#include<iostream>
using namespace std;
#include<cstdlib>
#include<queue>
#include<stack>
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;
};
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree();
	BinaryTree(const T* a,size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index=0;
		_root=_GreateTree(a,size,index,invalid);
	}
	BinaryTree(const BinaryTree<T>& t)
	{
		_root=_Copy(t._root) ;
	}
	void PrevOrder()   //ǰ��
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void PrevOrderNonR()  //�ǵݹ�    ջ
	{
		stack<Node*> s;
		Node* cur=_root;
		while(cur||!s.empty ())
		{
			while(cur)      //��������������
			{
				cout<<cur->_data <<" ";
			    s.push (cur);
			    cur=cur->_left ;
			}

			Node* top=s.top ();
			s.pop ();
			cur=top->_right ; 
		}
		cout<<endl;
	} 
	void InOrder()   //����
	{
		_InOrder(_root);
		cout<<endl;
	}
	void InOrderNonR()
	{
		stack<Node*> s;
		Node* cur=_root;
		while(cur||!s.empty ())
		{
			while(cur)
			{
				s.push (cur);
				cur=cur->_left ;
			}

			Node* top=s.top ();
			cout<<top->_data <<" ";
			s.pop ();
			cur=top->_right ;
		}
		cout<<endl;
	}
	void PostOrder()          //����
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void PostOrderNonR()
	{
		stack<Node*> s;
		Node* cur=_root;
		Node* prev=NULL;

		while(cur||!s.empty ())
		{
			while(cur)
			{
				s.push (cur);
				cur=cur->_left ;
			}
			Node* top=s.top ();
			if((top->_right ==NULL)||(top->_right ==prev))
			{
				cout<<top->_data <<" ";
				prev=top;
				s.pop ();
			}
			else
			{
				cur=top->_right ;
			}	
		}
        cout<<endl;
	}
	//�ҵ�K��ڵ�ĸ���
	size_t FindKLeve(size_t k)
	{
		return _FindKLeve(_root,k);
	}
	//Ҷ�ӽڵ����
	size_t LeafNum()
	{
		return _LeafNum(_root);
	}
	~BinaryTree()
	{
		_Destory(_root);
	}
	size_t Size()
	{
		return _Size(_root);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	Node* Find(const T& x)
	{
		return _Find(_root,x);
	}
	void LeveOder()    //��α���      ����
	{
		queue<Node*> q;
		if(_root)
			q.push (_root);

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

	//�ж�һ�Ŷ������Ƿ�Ϊ��ȫ������
	bool IsCompleteBinaryTree()
	{
		//��α�������NULLҲpush��ȥ
		queue<Node*> q;
		q.push (_root);
		Node* front=q.front ();
		while(front!=NULL)
		{
			q.pop ();
			q.push (front->_left );
			q.push (front->_right );
			front=q.front ();
		} 
		q.pop();
		while(!q.empty())
		{
            front=q.front ();
			if(front!=NULL)
			{
				return false;
			}
			q.pop();
		}
		return true;
	}

	//�ж�B�Ƿ�ΪA���ӽṹ
	bool IsSubStruct(BinaryTree<T>& b)
	{
		root1=_root;
		root2=b._root;

		return _IsSubStruct(root1,root2);
	}

	//�����������Զ�������ڵ��
	int GetFarthestDistance()
	{
		assert(_root);
		int distance=0;  //��¼��Զ�ľ���
		return _GetFarthestDistance(_root,distance);
	}

	//�������ڵ�����Ĺ�������
	Node* GetRecentlyAncestor(int root1,int root2)
	{
		stack<Node*> v1;  //���浽root1·��
		stack<Node*> v2;  //���浽root2·��

		int flag=0;       //�ж���û���ҵ�
		_GetRecentlyAncestor(_root,root1,v1,flag);
		flag=0;
		_GetRecentlyAncestor(_root,root2,v2,flag);
		Node* top1=v1.top ();
		Node* top2=v2.top ();
		Node* prev=top1;
		//����Ĺ������Ⱦ�����·���е�һ����ȵ�����ǰһ��
		while((!v1.empty())&&(!v2.empty()))
		{
			if(top1==top2)
			{
				prev=top1;
				v1.pop();
				if(!v1.empty ())
				    top1=v1.top();
				v2.pop();
				if(!v2.empty ())
					top2=v2.top();		
			}
			else
			{
				return prev;
			}
		}
		if(v1.empty()||v2.empty ())
		{
			return prev;
		}
	}
protected:
	bool _IsSubStruct(Node* root1,Node* root2)
	{
		if(root1==NULL)
			return false;
		if(root2==NULL)
			return true;
		if(root1->_data ==root2->_data )
			return _IsSubStruct(root1->_left ,root2->_left )&&
			_IsSubStruct(root1->_right ,root2->_right );
		else
			return _IsSubStruct(root1->_left ,root2)||
			_IsSubStruct(root1->_right ,root2);
		return false;

	}
	void _GetRecentlyAncestor(Node* root,int rootData,stack<Node*>& v,int& flag)
	{
		if(root==NULL||flag==1)//||flag==1��Ϊ�˱�ʾ�ҵ��Ľڵ���������������ȥ������������
			return;

		//�������
		_GetRecentlyAncestor(root->_left ,rootData,v,flag);
		_GetRecentlyAncestor(root->_right,rootData,v,flag);
		//��ǰ�ڵ�
		if(root->_data ==rootData||flag==1) //||flag==1��Ϊ�˱�ʾ�ҵ��Ľڵ��ٵ�ǰ��������
		{
			v.push(root);
			flag=1;
		}

	}
	 
	int _GetFarthestDistance(Node* root,int& distance)
	{
		if(root==NULL)
			return 0;
		//�������
		int left=_GetFarthestDistance(root->_left ,distance);
		int right=_GetFarthestDistance(root->_right ,distance);
		if(left+right>distance)  //����distance
			distance=left+right;
		return left>right?left+1:right+1;
	}
	size_t _LeafNum(Node* root)
	{
		 static size_t count=0;
		 if(root==NULL)
			 return count;
		 if((root->_left ==NULL)&&(root->_right ==NULL))
		 {
				++count;
				return count;
		 }
		 _LeafNum(root->_left );
		 _LeafNum(root->_right );
	}
	size_t _FindKLeve(Node* root,size_t k)
	{
		  if(root==NULL)
			  return 0;
		  if(k==1)
			  return 1;
		  return _FindKLeve(root->_left ,k-1)+_FindKLeve(root->_right ,k-1);
	}
	Node* _Find(Node* root,const T& x)
	{
		if(root==NULL)
			return NULL;
		if(root->_data==x )
			return root;
		
		Node* ret=_Find(root->_left,x );
		//������û���ҵ�������������
		if(ret==NULL)
		{
			ret=_Find(root->_right ,x);
		}
		return ret;
	}
	size_t _Depth(Node* root)
	{
		if(root==NULL)
			return 0;
		size_t LefD=_Depth(root->_left );
		size_t RigD=_Depth(root->_right );
		return LefD>RigD?LefD+1:RigD+1;
	}
	size_t _Size(Node* root)
	{/*
		static size_t count=0; 
		if(root==NULL)
		{
			return 0;
		}
		++count;
		_Size(root->_left );
		_Size(root->_right );

		return count;*/
		

		if(root==NULL)
			return 0;
		return _Size(root->_left )+_Size(root->_right )+1;
	}
	void _Destory(Node* root)
	{
		if(root)
		{
			_Destory(root->_left );
			_Destory(root->_right );
			delete root;
		}
	}
	void _PostOrder(Node* root)   
	{
		if(root)
		{
			_PostOrder(root->_left );
			_PostOrder(root->_right );
			cout<<root->_data <<" ";
		}
	}
	void _InOrder(Node* root)
	{
		if(root)
		{
			_InOrder(root->_left );
			 cout<<root->_data <<" ";
			 _InOrder(root->_right );
		}
	}

	void _PrevOrder(Node* root)
	{
		if(root)
		{
			cout<<root->_data <<" ";
			_PrevOrder(root->_left );
			_PrevOrder(root->_right );
		}
	}
	Node* _GreateTree(const T *a,size_t size,size_t& index,const T& invalid)
	{
		Node* root=NULL;
		if(a[index]!=invalid&&index<size)
		{
			root=new Node(a[index]);
			root->_left =_GreateTree(a,size,++index,invalid);
			root->_right =_GreateTree(a,size,++index,invalid);
		}
		return root;
	}

private:
	Node* _root;
};
	
void TestBinaryTree()
{
	int a[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> t(a,10,'#');
	t.PrevOrder ();
	BinaryTreeNode<int>* ret=t.GetRecentlyAncestor(3,1);
	cout<<ret->_data <<endl;
	//cout<<t.IsCompleteBinaryTree ();
	//t.PrevOrderNonR ();
	//t.InOrder ();
	//t.InOrderNonR ();
	//t.PostOrder ();
	//t.PostOrderNonR ();
	//cout<<t.LeafNum ()<<endl;
	//cout<<t.FindKLeve (3)<<endl;
	/*cout<<t.Size ()<<endl;
	cout<<t.Depth ()<<endl;
	BinaryTreeNode<int>* ret=t.Find (5);
	cout<<ret->_data <<endl;
	ret=t.Find (7);
	cout<<ret<<endl;
	t.LeveOder ();*/
}