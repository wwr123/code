#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
	int sv[2];
	int ret=socketpair(PF_LOCAL,SOCK_STREAM,0,sv);
	if(ret<0)
	{
		perror("socketpair");
		return 1;
	}
	pid_t id=fork();
    if(id==0)
	{
		char buf[1024];
		close(sv[0]); //关闭读端
		while(1)
		{		
			char* msg="hello world";
			//为了实现双向通信，
			//1.往写端写
			write(sv[1],msg,strlen(msg));
    	    //从写端读
			ssize_t s=read(sv[1],buf,sizeof(buf)-1);
    	    if(s>0)
			{
				buf[s]=0;
				printf("father echo:%s\n",buf);
			}
		}
		close(sv[1]);
	}
	else
	{
		char buf[1024];
		close(sv[1]);//关闭写端
		while(1)
		{
			ssize_t s=read(sv[0],buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s]=0;
				printf("child say:%s\n",buf);
				sleep(1);
				buf[0]='H';
				write(sv[0],buf,strlen(buf));
			}
		}
		close(sv[0]);
	}	
	return 0;
}
