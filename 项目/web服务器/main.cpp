#include"httpd.h"
#include"threadpool.cpp"
int startup(char* ip,int port)
{
	int listen_sock=socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock<0)
	{
		exit(2);
	}
	int opt=1;
    setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=inet_addr(ip);
	local.sin_family=AF_INET;
	socklen_t len=sizeof(local);
	if(bind(listen_sock,(struct sockaddr*)&local,len) < 0)
	{
		exit(3);
	}
	if(listen(listen_sock,5)<0)
	{
		exit(4);
	}
	return listen_sock;
}
int setnonblocking(int fd)
{
	int old_option=fcntl(fd,F_GETFL); //获得文件状态标志位
	int new_option=old_option|O_NONBLOCK;  
	fcntl(fd ,F_SETFL,new_option); //设置新的文件标志位
	return old_option;  //目的是以便以后回复到原来的标志位
}
void addfd(int epfd,int sock,bool falg)
{
	 epoll_event event;
	 event.data.fd=sock;
	 if(falg==false)
		event.events=EPOLLIN|EPOLLET|EPOLLRDHUP;
	 else
		 event.events=EPOLLIN|EPOLLET|EPOLLRDHUP|EPOLLONESHOT; //EPOLLONESHOT的意思是一个事件被线程之后就不会再被触发

	 epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&event); //把文件描述符注册到内核中
     setnonblocking(sock);   //把文件描述符设置为非阻塞
}
void close_sock(int epfd,int sock)
{
	epoll_ctl(epfd,EPOLL_CTL_DEL,sock,0);
	close(sock);
	sock=-1;
}


int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		exit(1);
	}
	int listen_sock=startup(argv[1],atoi(argv[2]));

	threadpool<httpd> t(10,1000);
	httpd arr[1000];
	for(int i=0;i<1000;i++)
	{
		arr[i].init(i);
	}

	//把listen_sock添加到epoll句柄中
	epoll_event events[1000];
	int epfd=epoll_create(10);
	addfd(epfd,listen_sock,false);

	while(1)
	{
//		daemon(1,0);
        printf("while start\n");
        int num=epoll_wait(epfd,events,1000,-1);
		if(num<0)
			break;
		printf("epoll wait end,num:%d\n",num);
		for(int i=0;i<num;i++)
		{
			int sockfd=events[i].data.fd;
			cout<<"sockfd:"<<sockfd<<endl;
			if(sockfd==listen_sock)
			{
				cout<<"listen sockfd:"<<sockfd<<endl;
			    struct sockaddr_in peer;
			    socklen_t len=sizeof(peer);
				int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
				if(sock<0)
				{
					continue;
				}
				printf("accept sock:%d\n",sock);
                addfd(epfd,sock,true); //获取到sock后，添加到epoll				
			}
	       else if(events[i].events&(EPOLLRDHUP))
	       {
		    	//关闭连接
		    	cout<<"quit"<<endl;
		    	close_sock(epfd,sockfd);
           }
			else if(events[i].events&EPOLLIN)
			{ 
				pthread_t id;
				printf("epoll in\n");
			    t.appendrequest(&arr[sockfd]);//把任务添加到队列中
				printf("append end\n");
			}
		}
	}
    close(epfd);
	close(listen_sock);
	return 0;
}
