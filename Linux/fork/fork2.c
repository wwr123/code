#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
	pid_t id1=fork();
	if(id1==0)//child
	{
		pid_t id2=fork();  //避免僵尸进程
		if(id2>0)  //father 直接退出
		{
			exit(0);
		}
		else
		{
			sleep(2); //保证他的父进程先执行
			printf("second child de father id=%d\n",getppid()); 
			//他会成为孤儿进程，1号进程将会收养他
			exit(0);
		}
	}
	else  //father
	{
		waitpid(id1,NULL,0); //立即来等待子进程结束
	}
	return 0;
}
