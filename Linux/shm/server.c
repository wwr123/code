#include"commont.h"
int main()
{
	int shmid=CreatShm();
	//sleep(10);
    int i=0;
    char* mem=(char*)shmat(shmid,NULL,0);
    sleep(4);
	//while(1)
	//{
	//	printf("%s",mem);
	//}
	//sleep(5);
	//printf("mem::%s\n",mem);
    dtShm(mem);
//printf("ret::%d\n",ret);
//       if(ret<0)
//{
//printf("faild1\n");
//}
	sleep(5);
	DestoryShm(shmid);
	return 0;
}
