#include<iostream>
using namespace std;
#include<stdlib.h>

struct Node
{
	Node* left;
	Node* right;
	int data;
	Node(int _data)
	{
		data=_data;
		left=NULL;
		right=NULL;
	}
};

//叶子节点的个数
void LeafNodeNumR(Node* root,int& num)
{
	if(root->left==NULL&&root->right==NULL)
	{
		num++;
		return;
	}
	else
	{
		if(root->left)
			LeafNodeNumR(root->left,num);
		if(root->right)
			LeafNodeNumR(root->right,num);
	}
	
}
int LeafNodeNum(Node* root)
{
	if(root==NULL)
		return 0;
	int num=0;
    LeafNodeNumR(root,num);
    return num;
}
void fun1()
{
	Node* node1=new Node(1);
	Node* node2=new Node(2);
	Node* node3=new Node(3);
	Node* node4=new Node(4);
	Node* node5=new Node(5);
	Node* node6=new Node(6);
	Node* node7=new Node(7);
	node1->left=node2;
	node1->right=node3;
	node2->left=node4;
	node3->left=node5;
	node5->left=node6;
	node5->right=node7;
	Node* node8=new Node(8);
	cout<<LeafNodeNum(node8)<<endl;
}
int main()
{
	fun1();
	return 0;
}
