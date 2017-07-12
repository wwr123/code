#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<assert.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<sys/select.h>
#include<unistd.h>

static void Usage(const char* arg)
{
	printf("Usage:%s [ip] [prot]\n",basename(arg));
}
int Startup(const char* ip,const char* port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	assert(sock>=0);
	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(atoi(port));
	local.sin_addr.s_addr=inet_addr(ip);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{	
		perror("bind");
		return -1;
	}
	if(listen(sock,5)<0)
	{
		perror("listen");
		return -2;
	}
	return sock;
}
int main(int argc,char* argv[])
{
	if(argc!=3)
		Usage(argv[0]);
	int listensock=Startup(argv[1],argv[2]);
	if(listensock<0)
		return -3;
    char fds[1024];
	fd_set rfds;
	fd_set wfds;
	fd_set efds; //selet只能处理一种异常情况：接受到带外数据
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);
	//buf[0]=listensock;
	int count=0;
	//memset(fds,0,sizeof(fds));
	struct timeval timeout={500,0};
		struct sockaddr_in client;
		socklen_t len=sizeof(client);
		int connetsock=accept(listensock,(struct sockaddr*)&client,&len);
		FD_SET(connetsock,&rfds);
		FD_SET(connetsock,&efds);
    while(1)
	{
		int ret=select(connetsock+1,&rfds,&wfds,&efds,&timeout);
		if(ret>0)
		{
			char buf[1024];
			//处理读事件
			if(FD_ISSET(connetsock,&rfds))
			{
				ssize_t s=recv(connetsock,buf,sizeof(buf)-1,0);
				if(s>0)
				{
					buf[s]=0;
					printf("client say:%s\n",buf);
					FD_CLR(connetsock,&rfds);
					FD_SET(connetsock,&wfds);
				}
			}
			//处理写事件
			else if(FD_ISSET(connetsock,&wfds))
			{
				char* msg="I am server\n";
				ssize_t s=send(connetsock,msg,strlen(msg),0);
				if(s<0)
				{
					perror("send");
		            continue;
				}
				FD_CLR(connetsock,&wfds);
				FD_SET(connetsock,&rfds);
			}
			//处理异常事件
		    else if(FD_ISSET(connetsock,&efds))
			{
				//最后一个参数表示，读取外带数据
				ssize_t s=recv(connetsock,buf,sizeof(buf),MSG_OOB);
				if(s>0)
					printf("client exception say:%s\n",buf);
			}
		}
		else if(ret<0)
		{
			perror("selecr");
			return -4;
		}
		else
		{
			printf("timeout\n");
		}

	}
    close(connetsock);
	close(listensock);
	return 0;
}
