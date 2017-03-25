#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#define SIZE 64
int ringbuf[SIZE];
sem_t blanks,datas;

void* product(void* arg)
{
	int count=0;
	while(1)
	{
		sem_wait(&blanks);  //p-->blanks--
		int data=rand()%1000;
		printf("product data::%d\n",data);
        ringbuf[count++]=data;
		count%=SIZE;  //keep ring
		sem_post(&datas);   //v-->datas++
	}
}

void* consumer(void* arg)
{
	int count=0;
	while(1)
	{
		sem_wait(&datas);
		int data=ringbuf[count++];
		printf("consumer data::%d\n",data);
        count%=SIZE; 
		sem_post(&blanks);
	}
}
int main()
{
	sem_init(&blanks,0,SIZE);
	sem_init(&datas,0,0);
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,product,NULL);
	pthread_create(&tid2,NULL,consumer,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	sem_destroy(&blanks);
	sem_destroy(&datas);
	return 0;
}
