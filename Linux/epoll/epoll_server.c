#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<stdlib.h>
#include<string.h>
typedef struct epbuf
{
	int fd;
	char buf[1024];
}epbuf_t,*epbuf_p,**epbuf_pp;

static epbuf_p alloc_epbuf(int fd)
{
	epbuf_p ptr=(epbuf_p)malloc(sizeof(epbuf_t));
	if(ptr==NULL)
	{
		perror("malloc");
		exit(5);
	}
	ptr->fd=fd;
	return ptr;
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("参数错误\n");
		exit(1);
	}
	int listen_sock=socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock<0)
	{
		perror("socket");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(argv[2]);
	local.sin_port=htons(atoi(argv[1]));
	socklen_t len=sizeof(local);
	if(bind(listen_sock,(struct sockaddr*)&local,len)<0)
	{
		perror("bind");
		exit(3);
	}
	if(listen(listen_sock,5)<0)
	{
		perror("listen");
		exit(4);
	}
	//1.创建一个epoll
	int epfd=epoll_create(200);
	struct epoll_event ev;
	ev.events=EPOLLIN|EPOLLET;
	ev.data.ptr=alloc_epbuf(listen_sock);
    //2.注册
	epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&ev);

	while(1)
	{
		int nums=0;
		struct epoll_event evs[32];
		int max_evs=32;
		int timeout=5000;
		switch(nums=epoll_wait(epfd,evs,max_evs,timeout))
		{
			case 0: //超时
				printf("timeout\n");
				break;
			case -1:
				perror("epoll_wait");
				break;
			default:
		 		{
		 			int i=0;
					for(;i<nums;i++)
					{
						int fd=((epbuf_p)(evs[i].data.ptr))->fd;
						if((evs[i].events&EPOLLIN)&&fd==listen_sock)
						{
							struct sockaddr_in peer;
							socklen_t len=sizeof(peer);
							int new_sock=accept(fd,(struct sockaddr*)&peer,&len);
							if(new_sock<0)
							{
								perror("accept" );
								continue;
							}
							ev.events=EPOLLIN;
							ev.data.ptr=alloc_epbuf(new_sock);
							epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&ev);
						}//if
						else if((evs[i].events&EPOLLIN)&&fd!=listen_sock)//读事件就绪
						{
							char* buf=((epbuf_p)(evs[i].data.ptr))->buf;
							ssize_t s=read(fd,buf,1023);
							if(s>0)
							{
								buf[s]=0;
								printf("%s\n",buf);
								//回写
								ev.events=EPOLLOUT;
								epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
							}
							else if(s==0)
							{
							    free(evs[i].data.ptr);
								evs[i].data.ptr=NULL;
								epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
							}
						}//else if
			     		else if((evs[i].events&EPOLLOUT)&&fd!=listen_sock)//写事件就绪
						{
							const char* msg="HTTP/1.0 200  OK \r\n\r\n<html><h1>HELLO WORLD!</h1></html>\n";
							write(fd,msg,strlen(msg));
						    free(evs[i].data.ptr);
							epoll_ctl(epfd,EPOLL_CTL_DEL,fd ,NULL);
		 		 		}
				 	}
				} 
		}
	}
	return 0;
}
