#include<iostream>
using namespace std;
#include<queue>
#include<vector>
#include<cstdlib>
typedef struct BinaryTreeNode
{
	BinaryTreeNode(const int& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	int _data;
}Node;

void LeveOder(Node* root)    //层次遍历      队列
	{
		queue<Node*> q;
		if(root)
			q.push (root);

		while(!q.empty ())
		{
			Node* front=q.front ();
			cout<<front->_data <<" ";
			q.pop ();
			if(front->_left )
				q.push (front->_left );
			if(front->_right )
				q.push (front->_right );
		}
		cout<<endl;
	}
Node* construct(int* startpreorder,int* endpreorder,int* startinorder,int* endinorder)
{
	int rootvalue=startpreorder[0];  //根节点的值
	Node* root=new Node(rootvalue);
	
	if(startpreorder==endpreorder)    //只有一个节点
	{
		if(startinorder==endinorder&&*startpreorder==*startinorder)
			return root;
		else
		{
			return NULL;
		}
	}
	int* inorderroot=startinorder;     //在中序中找到根节点的值
	while(inorderroot<=endinorder)
	{
		if(*inorderroot==rootvalue)
			break;
		inorderroot++;
	}
	if(inorderroot==endinorder&&*inorderroot!=rootvalue)
		return NULL;
	int LeftLenght=inorderroot-startinorder;       //左树的长度
	int* LeftPreorderEnd=startpreorder+LeftLenght;   //在前序中左子树最后的一个节点
	if(LeftLenght>0)
	{
		//构建左子树
		root->_left =construct(startpreorder+1,LeftPreorderEnd,
			startinorder,inorderroot-1);
	}
	if(LeftLenght<endpreorder-startpreorder)
	{
		//构建右子树
		root->_right =construct(LeftPreorderEnd+1,
			endpreorder,inorderroot+1,endinorder);
	}
	return root;
}
Node* Construct(int* preorder,int* inorder,int length)
{
	if(preorder==NULL||inorder==NULL||length<=0)
		return NULL;
	return construct(preorder,preorder+length-1,inorder,inorder+length-1);
}
void test1()
{
	int n=0;
	cin>>n;
	int *preorder=new int[n];
	int *inorder=new int[n];
	int num=0;
	int i=0;
	while(i<n)
	{
		cin>>num;
		 preorder[i]=num;
		++i;
	}
	i=0;
	while(i<n)
	{
		cin>>num;
	    inorder[i]=num;

		++i;
	}
	Node* root=Construct(preorder,inorder,n);
	LeveOder(root);
}
#include<string>
#include<math.h>
void test2(string& s)
{
	int len=s.size(); 
	int i=0;
	int j=len;
	double sum=0;
	for(i=0;i<len;++i)
	{
       sum+=(s[i]-'a')*pow(26.0,j-1);
	   --j;
	}
	cout<<sum<<endl;
}
int main()
{	
	vector<string> v;
    string s;
	while(cin>>s)
	{
		v.push_back (s);
	}
	int i=0;
	while(i<v.size())
	{
      test2(v[i]);
	  ++i;
	}
	//test1();
	//test3();
	system("pause");
	return 0;
}