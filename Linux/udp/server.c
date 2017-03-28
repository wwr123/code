#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Usage:%s [local_ip] [local_prot]\n",argv[0]);
		return 1;
	}
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("socket");
		return 2;
	}

	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(atoi(argv[2]));
	local.sin_addr.s_addr=inet_addr(argv[1]);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		return 3;
	}
	struct sockaddr_in peer;
	char buf[1024];
	socklen_t  len=sizeof(peer);	
	while(1)
	{
		size_t s=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&peer,&len);
		if(s>0)
		{
			printf("get a msg :%s:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
			buf[s]=0;
			printf("client#%s\n",buf);
		}
		else if(s==0)
		{
			printf("client is quit\n");
			break;
		}
		else
		{
			perror("recvfrom");
		}
	}
	close(sock);
	return 0;
}
