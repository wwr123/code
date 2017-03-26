#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int g_val=0;
pthread_rwlock_t rwlock;

void* readerRun(void* arg)
{
	int ret=pthread_rwlock_rdlock(&rwlock);
	if(ret==0)
	{
		g_val--;
		printf("reader data::%d\n",g_val);
		pthread_rwlock_unlock(&rwlock);
	}
}

void* writerRun(void* arg)
{
	sleep(3);
	int ret=pthread_rwlock_wrlock(&rwlock);
	if(ret==0)
	{
		g_val++;
		printf("writer data::%d\n",g_val);
		pthread_rwlock_unlock(&rwlock);
	}
}
int main()
{
	pthread_rwlock_init(&rwlock,NULL);
	pthread_t reader,writer;
    pthread_create(&reader,NULL,readerRun,NULL);
	pthread_create(&writer,NULL,writerRun,NULL);
	pthread_join(reader,NULL);
	pthread_join(writer,NULL);
	pthread_rwlock_destroy(&rwlock);
	return 0;
}
