#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int fd[2];
	if(pipe(fd)==-1)
	{
		perror("pipe");
		return 1;
	}
	pid_t id=fork();
	if(id==0)
	{
		//child
		close(fd[0]); //clode read
		int count=6;
		const char* msg="abcdefg";
//		while(count--)
		while(1)
		{
		    ssize_t ret=write(fd[1],msg,strlen(msg));
			if(ret==-1)
			{
				perror("write");
				return 1;
			}
		}
		close(fd[1]);
	}
	else
	{
		//father
		close(fd[1]);  //close write
		char* buf[100];
		int count=4;
		while(count--)
		{
			ssize_t ret=read(fd[0],buf,sizeof(buf)-1);
			if(ret==0)
			{
				//read faild
				perror("read");
				return 1;
			}
			else
			{
				buf[ret]='\0';
				printf("child write is::%s\n",buf);
			}
		}
		    close(fd[0]);
	        int status=0;
			pid_t waitret=waitpid(id,&status,0);
			printf("%d,%s,%s\n",status&0xff,strerror(status&0xff),(status>>8)&0xff);
		//	close(fd[0]);
	}
	return 0;
}
