#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<ctype.h>
#include<stdlib.h>

int main()
{
	while(1)
	{
    printf("[wwr@localhost ]#");
	fflush(stdout);
	char line[1024];
	ssize_t s=read(0,line,1024);
	if(s>0)
	{
		line[s]=0;
	}
	else
	{
		printf("read fail\n");
		continue;
	}
	
	int j = 0;
    char* myargv[20];
	int i=1;
	char* start=line;
	myargv[0]=start;

	while(*start)
	{
		if(isspace(*start))
		{
			//shikongge
			*start='\0';
			start++;
			myargv[i++]=start;
		}
		else
		{
			start++;
		}
	}
	myargv[i-1]=NULL;

    pid_t id=fork();
	if(id==0)
	{
		//child
		execvp(myargv[0], myargv);
		perror("error");
		exit(1);
	}
	else
	{
		//father
		sleep(1);
		wait(NULL);
	}
	}
	return 0;
}

