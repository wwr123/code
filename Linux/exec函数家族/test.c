#include<unistd.h>
#include<stdio.h>
//int main()
//{
//	pid_t id=fork();
//    if(id==0)
//	{
//		execl("/bin/ls","ls","-a","-l",NULL);
//	}
//	else
//	{
//		waitpid(id,NULL,0);
//	}
//	return 0;
//}
//int main()
//{
//	pid_t id=fork();
//	if(id==0)
//	{
//		char* argv[]={"ls","-a","-l",NULL};
//		execv("/bin/ls",argv);
//	}
//	else
//	{
//		waitpid(id,NULL,0);
//	}
//	return 0;
//}
int main()
{
	pid_t id=fork();
	if(id==0)
	{
		char* const envp[]={"MYPATH=/A/B",NULL};
		execle("/home/wwr/code/exec/myexec","./myexec",NULL,envp);
	}
	else
	{
		waitpid(id,NULL,0);
	}
	return 0;
}
