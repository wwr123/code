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
	void PrevOrder()   //前序
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void PrevOrderNonR()  //非递归    栈
	{
		stack<Node*> s;
		Node* cur=_root;
		while(cur||!s.empty ())
		{
			while(cur)      //把左子树访问完
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
	void InOrder()   //中序
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
	void PostOrder()          //后序
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
	//找第K层节点的个数
	size_t FindKLeve(size_t k)
	{
		return _FindKLeve(_root,k);
	}
	//叶子节点个数
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
	void LeveOder()    //层次遍历      队列
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
protected:
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
		//左子树没有找到，从右子树找
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
	t.PrevOrderNonR ();
	t.InOrder ();
	t.InOrderNonR ();
	t.PostOrder ();
	t.PostOrderNonR ();
	cout<<t.LeafNum ()<<endl;
	//cout<<t.FindKLeve (3)<<endl;
	/*cout<<t.Size ()<<endl;
	cout<<t.Depth ()<<endl;
	BinaryTreeNode<int>* ret=t.Find (5);
	cout<<ret->_data <<endl;
	ret=t.Find (7);
	cout<<ret<<endl;
	t.LeveOder ();*/
}