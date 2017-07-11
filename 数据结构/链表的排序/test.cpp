#include<iostream>
using namespace std;
#include<stdlib.h>

namespace ListTopic
{
	struct Node
	{
		Node(int data)
			:data(data)
			,next(NULL)
		{}
		int data;
		Node* next;
	};
};
using namespace ListTopic;
//链表的排序
//可以用归并，冒泡，快排，选择
//1.实现用冒泡法排序链表,升序
void BubbleSortList(Node* head)
{
	if(head==NULL||head->next==NULL)
		return;
	Node* tail=NULL;
	Node* cur=head->next;
	Node* prev=head;
	while(cur!=tail)
	{
		bool falg=false;
		//单趟排序
		while(cur!=tail)
		{
			if(cur->data<prev->data)
			{
				swap(cur->data,prev->data);
				falg=true;
			}
			cur=cur->next;
			prev=prev->next;
		}
		if(falg==false)
			break;
		tail=prev;
		cur=head->next;
		prev=head;
	}
}
//快排
void QuickSortList(Node* head,Node* tail)
{
	if(head==NULL||head->next==NULL||head==tail||head->next==tail)
		return;
	//前后指针法
	Node* prev=head;   //指向的永远比key大
	Node* cur=head->next; //找key小的值
	int key=head->data;
	while(cur!=tail)
	{
		if(cur->data<key)
		{
			prev=prev->next;
			if(prev!=cur)
				swap(prev->data,cur->data);
		}
		cur=cur->next;
		swap(prev->data,head->data);
	}
	QuickSortList(head,prev);
	QuickSortList(prev->next,tail);
}
 void fun1()
 {
	 Node* node1=new Node(2);
	 Node* node2=new Node(8);
	 Node* node3=new Node(6);
	 Node* node4=new Node(9);
	 Node* node5=new Node(5);
	 node1->next=node2;
	 node2->next=node3;
	 node3->next=node4;
	 node4->next=node5;
	 node5->next=NULL;
	// BubbleSortList(node1);
	 QuickSortList(node1,NULL);
	 Node* newnode=node1;
 }
int main()
{
	fun1();
	system("pause");
	return 0;
}