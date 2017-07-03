#include<stdio.h>
#include<string.h>
#include<unistd.h>
//第一个版本，不能向所执行的命令传递参数
//例如：ls /ls -l就错了
#define MAXSIZE 80
int main()
{
	char buf[MAXSIZE];
	int statue;
	while(fgets(buf,MAXSIZE,stdin)!=NULL)
	{
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]=0;    //exec函数要是以‘0’结尾

	    pid_t id=fork();
 		if(id==0)
 		{
 			execlp(buf,buf,NULL);
 		}
 		else
 		{
 			waitpid(id,&statue,0); //非阻塞等待子进程退出
 		}
	}
	return 0;
}
