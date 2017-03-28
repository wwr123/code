#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Usage:%s [peer_ip] [peer_port]\n",argv[0]);
		return 1;
	}
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("socket");
		return 2;
	}
	
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	char buf[1024];
	while(1)
	{
		printf("please Enter#");
		fflush(stdout);
		size_t _s=read(0,buf,sizeof(buf)-1);
		buf[_s-1]=0;
		size_t s=sendto(sock,buf,sizeof(buf),0,(struct sockaddr*)&server,sizeof(server));
        if(s<0)
		{
			perror("sendto");
			continue;
		}
	}
	close(sock);
	return 0;
}
