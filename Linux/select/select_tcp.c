#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define _SIZE_ 128
int gfds[_SIZE_];
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		exit(1);
	}
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("sock");
		exit(2);
	}
	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(argv[1]);
	local.sin_port=htons(atoi(argv[2]));
	socklen_t len=sizeof(local);
	if(bind(sock,(struct sockaddr*)&local,len)<0)
	{
		perror("bind");
		exit(3);
	}
    if(listen(sock,5)<0)
	{
		perror("listen");
		exit(4);
	}

	//select
	int i=0;
	for(;i<_SIZE_;i++)
	{
		gfds[i]=-1;
	}
	gfds[0]=sock;

	while(1)
	{
		int max_fd=-1;
		struct timeval timeout={5,0};
		fd_set rfds;
		FD_ZERO(&rfds);
		int j=0;
		for(;j<_SIZE_;j++)
		{
			if(gfds[j]>=0)
				FD_SET(gfds[j],&rfds);  //设置读集
			if(max_fd<gfds[j])
				max_fd=gfds[j];  //更新最大文件描述符
		}
		switch(select(max_fd+1,&rfds,NULL,NULL,&timeout))
		{
			case 0:
				printf("timeout\n");
				break;
			case -1:
				printf("faild\n");
				break;
		    default:  //成功
				{	
                int k=0;
				for(;k<_SIZE_;k++)
				{
					//没就绪
					if(gfds[k]<0)
					{
						continue;
					}
					if(gfds[k]==sock&&FD_ISSET(gfds[k],&rfds))
					{
						struct sockaddr_in peer;
						socklen_t len=sizeof(peer);
						int new_sock=accept(gfds[k],(struct sockaddr*)&peer,&len);
						int m=0;
						for(;m<_SIZE_;m++)
						{
							if(gfds[m]==-1)
							{
								gfds[m]=new_sock;
							 	break;
							} 
						}
						if(m==_SIZE_)
						{
							close(new_sock);
						}
					}//if
					else if(FD_ISSET(gfds[k],&rfds))
					{
						char buf[128];
						int s=read(gfds[k],buf,sizeof(buf)-1);
						if(s==0)//对端连接关闭了，行当于读到文件结尾
						{
							printf("client is quit\n");
							close(gfds[k]);
							gfds[k]=-1;
						}
						if(s>0)
						{
							buf[s-1]=0;
							printf("%s\n",buf);
						}
					}

				}
				}
		}
	}
}
