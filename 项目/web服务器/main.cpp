#include"httpd.h"
#include"threadpool.cpp"
#include<time.h>
#define TIMEOUT 15
int fd[2];
static int epfd=0;
static time_heap time_he;

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
}

void addsig(int sig,void (handler) (int))
{
	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));
	sa.sa_handler=handler;
	sa.sa_flags|=SA_RESTART; //被中断时，重启
    //将所有信号添加到mask字段中
	sigfillset(&sa.sa_mask);  //在信号处理函数时，屏蔽mask字段中的信号，处理完后，信号被激活
	assert(sigaction(sig,&sa,NULL)!=-1);
}
void sig_handler(int sig)
{
	send(fd[1],(char*)&sig,1,0);
}
void addsig1(int sig)
{
	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));
	sa.sa_handler=sig_handler;   //存放的是函数指针
	sa.sa_flags|=SA_RESTART;
	sigfillset(&sa.sa_mask);
	assert(sigaction(sig,&sa,NULL)!=-1);
}
//时间到期时调用的函数
//删除非活动连接sock上的注册事件
void cb_func(client_data* user)
{
	epoll_ctl(epfd,EPOLL_CTL_DEL,user->sockfd,0);
	close(user->sockfd);
	printf("close sockv fd:%d\n",user->sockfd);
}
//超时的处理函数
void time_handler()
{
	time_he.tick(); //即执行心跳函数，即检测是否有连接到时
	alarm(TIMEOUT); //alarm函数只会触发一次信号，需要不断的触发
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		exit(1);
	}
	int listen_sock=startup(argv[1],atoi(argv[2]));
    
	//忽略SIGPIPE信号
	//SIGPIPE:服务器关闭了连接，客户端还在发送数据，就会触发这个信号，告诉服务器不用写了
	//SIG_IGN:是无返回值的函数指针，表示忽略信号的处理程序
	addsig(SIGPIPE,SIG_IGN);
    
	//创建线程池
	threadpool<httpd> t(10,1000);
	httpd arr[1000];
	for(int i=0;i<1000;i++)
	{
		arr[i].init(i);
	}
    
	//创建一个epoll句柄
	epoll_event events[1000];
	epfd=epoll_create(10);
	//把listen_sock添加到epoll句柄中
	addfd(epfd,listen_sock,false);

	//创建一个全双工管道，子进程将检测到超时的信号写到管道中，父进程读
	int ret=socketpair(PF_UNIX,SOCK_STREAM,0,fd);
	assert(ret!=-1);
	setnonblocking(fd[1]); //写端设置为非阻塞
	addfd(epfd,fd[0],true); //把读端添加到epoll中,用来监听信号是否触发
	
	//安装信号
	addsig1(SIGALRM); //闹钟信号
	addsig1(SIGTERM); //终止进程信号
    
	bool stop_server=false; //判断是否为终止进程信号
	int timeout=false;  //判断是否超时
	alarm(TIMEOUT); //设置闹钟函数
    client_data user[1000];  //保存用户的数据

	while(!stop_server)
	{
		//daemon(1,0);
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
				//将数据添加到用户数据类中
				user[sock].addr=peer;
				user[sock].sockfd=sock;
				//创建一个定时器
				heap_timer* timer=new heap_timer;
				timer->user_data=&user[sock];
				timer->cb_func=cb_func;
				time_t cur=time(NULL);
				timer->expire=cur+3*TIMEOUT;
				user[sock].timer=timer;  //将定时器添加到用户数据类中
				time_he.add_timer(timer); //添加到时间堆中

				printf("add sucess\n");
			}
			else if(sockfd==fd[0]&&(events[i].events&EPOLLIN))  //信号被触发了
			{
				int sig;
				char buf[1024];
				int ret=recv(fd[0],buf,sizeof(buf),0);
				if(ret<=0)
				{
					continue;
				}
				else
				{
					for(int i=0;i<ret;i++)
					{
						switch(buf[i])
						{
							case SIGALRM:
								{
									timeout=true; //超时了
								    break;
								}
							case SIGTERM:
								stop_server=true;
						}
					}
				}
			}
	        else if(events[i].events&(EPOLLRDHUP)) //读端关闭 
	        {
				//从时间堆中删除定时器，并执行他的回调函数，即从epoll中清除
		    	//关闭连接
		    	//close_sock(epfd,sockfd);
				heap_timer* timer=user[sockfd].timer;
				cb_func(&user[sockfd]); 
				if(!timer)
				{
					time_he.delete_timer(timer);
				}
            }
			else if(events[i].events&EPOLLIN)
			{ 
				printf("start epoll in\n");
				//读事件就绪，调整对应定时器，以延迟关闭连接
				heap_timer* timer=user[sockfd].timer;
				printf("user->sockfd:%d\n",timer->user_data->sockfd);
				printf("timer get:%d\n",timer->expire);

				time_t cur=time(NULL);
				printf("time:%d\n",time);
				timer->expire=cur+3*TIMEOUT;
				printf("expire:%d\n",timer->expire);

				printf("adjust start\n");

				time_he.adjust_timer(timer);
                
				printf("epoll in\n");
			    t.appendrequest(&arr[sockfd]);//把任务添加到队列中
				printf("append end\n");
				
			}
		}
		if(timeout) //超时了
		{
			time_handler();
			timeout=false;
		}
	}
    close(epfd);
	close(listen_sock);
	return 0;
}
