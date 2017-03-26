#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>

static void Usage(const char* pro)
{
	printf("Usage:%s[ip][prot]\n",pro);
}
int main(int argc,char* argv[])
{
    if(argc!=3)
	{
		Usage(argv[0]);
		return -1;
	}
	int client_sock=socket(AF_INET,SOCK_STREAM,0);
	if(client_sock<0)
	{
		perror("socket");
		return -2;
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	if(connect(client_sock,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("connect");
		return -3;
	}
	char buf[1024];
	while(1)
	{
		ssize_t s=read(0,buf,sizeof(buf)-1);
		buf[s]=0;
		write(client_sock,buf,s);
	}
	close(client_sock);
	return 0;
}
