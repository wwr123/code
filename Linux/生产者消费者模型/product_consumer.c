#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;
typedef struct node
{
	int data;
	struct node* next; 
}node_t,*node_p,**node_pp;


node_p alloc_node(int data)
{
	node_p node=(node_p)malloc(sizeof(node_t));
	if(node==NULL)
	{
		perror("malloc");
		return NULL;
	}
	node->data=data;
	node->next=NULL;
	return node;
}

void InitList(node_pp head)
{
	*head=alloc_node(0);
}

void PushHead(node_p head,int data)
{
	node_p new_node=alloc_node(data);
	new_node->next=head->next;
	head->next=new_node;
}

void del_node(node_p node)
{
	assert(node);
	free(node);
}

int IsEmpty(node_p head)
{
	assert(head);
	if(head->next)
	{
		return 0;//is not
	}
	return 1; //is
}

void PopHead(node_p head,int* data)
{
	if(IsEmpty(head))
		return;
	node_p delete_node=head->next;
	head->next=delete_node->next;
	*data=delete_node->data;
	del_node(delete_node);  
}

void ShowList(node_p head)
{
	assert(head);
	node_p node=head->next;
	while(node)
	{
		printf("%d ",node->data);
        node=node->next;
	}
	printf("\n");
}

void DestoryList(node_p head)
{
	assert(head);
	int data=0;
	while(head->next)
	{

		PopHead(head,&data);
	}
	del_node(head);
}

void* thread_product(void* arg)
{
	node_p head=(node_p)arg;
	while(1)
	{
		sleep(1);
        int data=rand()%10000;
		pthread_mutex_lock(&mylock);
		PushHead(head,data);
		pthread_mutex_unlock(&mylock);
		pthread_cond_signal(&mycond);
		printf("product done,data::%d\n",data);
	}
}

void* thread_consumer(void* arg)
{
	node_p head=(node_p)arg;
	int data=0;
	while(1)
	{
		pthread_mutex_lock(&mylock);
		while(IsEmpty(head))
		{
			pthread_cond_wait(&mycond,&mylock);
		}
		PopHead(head,&data);
		pthread_mutex_unlock(&mylock);
		printf("consumer done,data::%d\n",data);
	}
}
int main()
{
	node_p head=NULL;
    InitList(&head);

	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread_product,(void*)head);
	pthread_create(&tid2,NULL,thread_consumer,(void*)head);
    pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&mylock);
	pthread_cond_destroy(&mycond);
	return 0;
}

//int main()
//{
//	node_p head=NULL;
//	InitList(&head);
//  int i=0;
//	for(;i<10;i++)
//	{
//		PushHead(head,i);
//		ShowList(head);
//	}
//	int data=0;
//	for(;i>=5;i--)
//	{
//		PopHead(head,&data);
//		ShowList(head);
//	}
//	DestoryList(head);
//	ShowList(head);
//	return 0;
//}
