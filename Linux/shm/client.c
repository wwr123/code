#include"commont.h"
int main()
{
	int shmid=GetShm();
	sleep(10);
    char* mem=(char*)shmat(shmid,NULL,0);
    //sleep(10);
	int i=0;
   // while(1)
	//{
		//sleep(1);
		//mem[i++]='A';
	//	i%=(SIZE-1);//daolezuihouqianyigeweizhi
	//	mem[i]='\0';
	//}
	//sleep(5);
        sleep(5);
int ret=	shmdt(mem);
//if(ret<0)
//{
//printf("faild\n");
//}
//	sleep(5);
	return 0;
}
