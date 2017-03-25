#include"commont.h"
int CommontShm(int flag)
{
	key_t key=ftok(PATHNAME,PROJID);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
//	printf("key::%d\n",key);
	int shmid=shmget(key,SIZE,flag);
	if(shmid<0)
	{
		perror("shmget");
		return -1;
	}
//	printf("shmid::%d\n",shmid);
	return shmid;
}
int CreatShm()
{
	return CommontShm(IPC_CREAT|IPC_EXCL|0666);
}
int GetShm()
{
    return CommontShm(IPC_CREAT);
}
int DestoryShm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,NULL)<0)
	{
		perror("shmctl");
		return -1;
	}
	return 0;
}

int dtShm(const void* arg)
{
	if(shmdt(arg) < 0)
	{
		perror("shmdt");
		return -1;
	}
	return 0;
}
