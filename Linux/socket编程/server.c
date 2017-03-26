#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>

int StartUp(int _port,char* _ip)
{
	//1.scoket
	int listen_sock=socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock<0) //failed
	{		
		perror("scoket");
		exit(1);
	}
	//2.bind
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(_port);
	local.sin_addr.s_addr=inet_addr(_ip);
	//socklen_t len=sizeof(local);
    if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(2);
	}
	//3.listen
	if(listen(listen_sock,5)<0)
	{
		perror("listen");
		exit(3);
	}
	return listen_sock;
}
int main(int argc,char* argv[])
{
    if(argc!=3)
	{
		printf("%s:[ip][prot]\n",argv[0]);
	}
	struct sockaddr_in remote;
	socklen_t len=sizeof(remote);
	int listen_sock=StartUp(atoi(argv[2]),argv[1]);
    char buf[1024];
	while(1)
	{	
		int client_sock=accept(listen_sock,(struct sockaddr*)&remote,&len);
		if(client_sock<0)
		{
			perror("accept");
			continue;
	    }
		while(1)
		{
			int s=read(client_sock,buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s-1]=0;
				printf("client#%s\n",buf);
			}
			else
			{
	
				printf("client is quit\n");
				break;
			}
		}
	}
    close(listen_sock);
	return 0;
}
