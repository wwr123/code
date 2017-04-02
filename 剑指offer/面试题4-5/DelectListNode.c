#include<stdio.h>
#include<assert.h>
#include<malloc.h>
struct ListNode
{
	int data;
	struct ListNode* next;
};
void CreatListNode(struct ListNode** phead, int data)
{
	struct ListNode* pnew=malloc(sizeof(struct ListNode));
	pnew->data=data;
	pnew->next=NULL;
	if(*phead==NULL) //空链表
		*phead=pnew; //phead是一个指向指针的指针，每次保存头节点的地址
	else
	{
		struct ListNode* cur=*phead;
		while(cur->next!=NULL)//找到最后一个节点
			cur=cur->next;
		cur->next=pnew;
	}
}
void Destory(struct ListNode** phead)
{
	assert(phead);
	struct ListNode* cur=*phead;
	struct ListNode* del=NULL;
	while(cur)
	{
		del=cur;
		cur=cur->next;
		free(del);
	}
}
void Display(struct ListNode** phead)
{
	assert(phead);
	struct ListNode* cur=*phead;
	while(cur)
	{
		printf("%d->",cur->data);
		cur=cur->next;
	}
	printf("NULL\n");
}
//删除某个含某值的节点
void RemoveNode(struct ListNode** phead,int data)
{
	assert(phead);
	struct ListNode* cur=*phead;
	struct ListNode* prev=*phead;
	if(cur->data==data)
	{
		*phead=cur->next;
		prev->next=NULL;
		free(prev);
		return;
	}
	while(cur)
	{
		if(cur->data==data)
		{
			prev->next=cur->next;
		    free(cur);
			cur->next=NULL;
			return;
		}
		else
		{
			prev=cur;
			cur=cur->next;
		}
	}
}
//递归的思想
void printf_prevtoend(struct ListNode* cur)
{
	if(cur==NULL)
	{
		return;
	}
	else
		printf_prevtoend(cur->next);
	printf("%d->",cur->data);
}
void PrintList_prevtoend(struct ListNode** phead)
{
	assert(phead);
	struct ListNode* cur=*phead;
	printf_prevtoend(cur);
	printf("NULL\n");
}
int main()
{
    struct ListNode* phead=NULL;
    CreatListNode(&phead,1);
    CreatListNode(&phead,2);
    CreatListNode(&phead,3);
    CreatListNode(&phead,4);
    CreatListNode(&phead,5);
	Display(&phead);
	//RemoveNode(&phead,1);
	PrintList_prevtoend(&phead);
	//Display(&phead);
	Destory(&phead);
}
