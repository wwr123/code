#include"common.h"
int main()
{
	int semid=CreatSemSet(1);
//	printf("semid::%d\n",semid);
	InitSemSet(semid,0);
	pid_t id = fork();
	if(id == 0)
	{//child
		int semid = GetSemSet();		
		
		while(1)
		{
			P(semid,0);
		
			printf("A");
			fflush(stdout);
			usleep(101000);
			printf("A");
		 	fflush(stdout);
			usleep(50000);
		
			V(semid,0);	
		}
	}
	else
	{//father
		while(1)
		{
			P(semid,0);
			
		    printf("B");
			fflush(stdout);
			usleep(102100);
			printf("B");
			fflush(stdout);
			usleep(210000);
			
			V(semid,0);	
		}	
		wait(NULL);
		DestorySemSet(semid);
	}
	return 0;
}
