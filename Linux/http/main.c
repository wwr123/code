#include<stdio.h>
#include<stdlib.h>
#include"httpd.h"
int startup(char* ip,int port)
{
	int listen_sock=socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock<0)
	{
		print_log("socket faild",FATAL);
		exit(2);
	}
//	int opt=1;
//	setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=inet_addr(ip);
	local.sin_family=AF_INET;
	socklen_t len=sizeof(local);
	if(bind(listen_sock,(struct sockaddr*)&local,len) < 0)
	{
		print_log("bind faild",FATAL);
		exit(3);
	}
	if(listen(listen_sock,5)<0)
	{
		print_log("listen faild",FATAL);
		exit(4);
	}
	return listen_sock;
}

int main(int argc,char* argv[])
{
    daemon(1,0);
	if(argc!=3)
	{
		printf("Usage: %s [ip] [port]\n",argv[0]);
		exit(1);
	}
	int listen_sock=startup(argv[1],atoi(argv[2]));
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);
	while(1)
	{
		printf("accept start\n");
		int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
		printf("accept end\n");
		if(sock<0)
		{
			print_log("accept faild",WARNING);
			exit(5);
		}
        pthread_t id;
		printf("pthread_create start\n");
		pthread_create(&id,NULL,accept_handler,(void*)sock);
       printf("pthread_create end\n");	
	   sleep(5);
	}
}
