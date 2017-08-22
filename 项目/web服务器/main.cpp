#include<stdio.h>
#include<stdlib.h>
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

void addfd(int epfd,int sock)
{
 	 printf("add fd\n");
	 epoll_event event;
	 event.data.fd=sock;
	 event.events=EPOLLIN|EPOLLET|EPOLLRDHUP;
	 epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&event);
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
	addfd(epfd,listen_sock);

	while(1)
	{
       // cout<<"while"<<endl;	
//		daemon(1,0);
        int num=epoll_wait(epfd,events,1000,-1);
		if(num<0)
			break;
	//	printf("epoll wait end,num:%d\n",num);
		for(int i=0;i<num;i++)
		{
			int sockfd=events[i].data.fd;
		//	cout<<"sockfd:"<<sockfd<<endl;
			if(sockfd==listen_sock)
			{
			//	cout<<"listen sockfd:"<<sockfd<<endl;
			    struct sockaddr_in peer;
			    socklen_t len=sizeof(peer);
				int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
				if(sock<0)
				{
					continue;
				}
			//	printf("accept sock:%d\n",sock);
				addfd(epfd,sock);
			}
			else if(events[i].events&EPOLLIN)
			{ 
				pthread_t id;
			//	printf("epoll in\n");
			    t.appendrequest(&arr[sockfd]);//把任务添加到队列中
				//cout<<"append end"<<endl;	
			}
		}
	}
    close(epfd);
	close(listen_sock);
	return 0;
}
