#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
int Sock(char* ip,int port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
		exit(2);
	struct sockaddr_in local;
	local.sin_port=htons(port);
	local.sin_family=AF_INET;
    local.sin_addr.s_addr=inet_addr(ip);
	socklen_t len=sizeof(local);
	if(bind(sock,(struct sockaddr*)&local,len)<0)
		exit(3);
	if(listen(sock,5)<0)
        exit(4);
	return sock;
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Usage:%s ip port\n",argv[0]);
		exit(1);
	}
	int listen_sock=Sock(argv[1],atoi(argv[2]));
    int epfd=epoll_create(5); 
	struct epoll_event event;
	event.data.fd=listen_sock;
	event.events=EPOLLIN|EPOLLET;
	epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&event);
	struct epoll_event events[5];

	while(1)
	{
		int num=epoll_wait(epfd,events,5,-1);
		int i=0;
		for(i=0;i<num;i++)
		{
			int sockfd=events[i].data.fd;
			if(sockfd==listen_sock)
			{
				struct sockaddr_in client;
				socklen_t len=sizeof(client);
				int sock=accept(listen_sock,(struct sockaddr*)&client,&len);
				struct epoll_event event;
				event.data.fd=sock;
				event.events=EPOLLIN|EPOLLET;
				epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&event);
			}
			else if(events[i].events & EPOLLIN)
			{
				char buf[1024];
				size_t s=read(sockfd,buf,sizeof(buf)-1);
				if(s>0)
					buf[s]=0;
				printf("%s\n",buf);
				char* msg="hello";
			    write(sockfd,msg,strlen(msg));
			}
		}

	}
	return 0;
} 
