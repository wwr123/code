#include"common.h"
static int CommonSemSet(int nums,int flag)
{
	key_t key=ftok(PATHNAME,PROJID);
	if(key<0)//faild
	{
		perror("ftok");
		return -1;
	}
	int semid=semget(key,nums,flag);
	if(semid<0)//faild
	{
		perror("semget");
		return -2;
	}
	return semid;
}
int CreatSemSet(int nums)
{
    return CommonSemSet(nums,IPC_CREAT|IPC_EXCL|0666);
}
int GetSemSet()
{
	return CommonSemSet(0,0);//??
}
int DestorySemSet(int semid)
{
	int ret=semctl(semid,0,IPC_RMID);
	if(ret == -1)//faild
	{
		perror("semctl");
		return -1;
	}
	return 0;
}
int SemOP(int semid,int which,int op)
{
	struct sembuf s;
	s.sem_num=which;
	s.sem_op=op;
	s.sem_flg=0;//???
	int ret=semop(semid,&s,1);
	if(ret<0)
	{
		perror("semop");
		return -1;
	}
	return 0;
}
int P(int semid,int which)
{
	return SemOP(semid,which,-1);
}
int V(int semid,int which)
{
	return SemOP(semid,which,1);
}	
int InitSemSet(int semid,int which)
{
	union semun un;
	un.val=1;
	int ret=semctl(semid,which,SETVAL,un);
	if(ret<0)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}
