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

	//判断一颗二叉树是否为完全二叉树
	bool IsCompleteBinaryTree()
	{
		//层次遍历，把NULL也push进去
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

	//判断B是否为A的子结构
	bool IsSubStruct(BinaryTree<T>& b)
	{
		root1=_root;
		root2=b._root;

		return _IsSubStruct(root1,root2);
	}

	//求二叉树中最远的两个节点的
	int GetFarthestDistance()
	{
		assert(_root);
		int distance=0;  //记录最远的距离
		return _GetFarthestDistance(_root,distance);
	}

	//求两个节点最近的公共祖先
	Node* GetRecentlyAncestor(int root1,int root2)
	{
		stack<Node*> v1;  //保存到root1路径
		stack<Node*> v2;  //保存到root2路径

		int flag=0;       //判断有没有找到
		_GetRecentlyAncestor(_root,root1,v1,flag);
		flag=0;
		_GetRecentlyAncestor(_root,root2,v2,flag);
		Node* top1=v1.top ();
		Node* top2=v2.top ();
		Node* prev=top1;
		//最近的公共祖先就是在路径中第一不相等的数的前一个
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
		if(root==NULL||flag==1)//||flag==1是为了表示找到的节点在最子树，不用去访问右子树了
			return;

		//后序遍历
		_GetRecentlyAncestor(root->_left ,rootData,v,flag);
		_GetRecentlyAncestor(root->_right,rootData,v,flag);
		//当前节点
		if(root->_data ==rootData||flag==1) //||flag==1是为了表示找到的节点再当前的子树中
		{
			v.push(root);
			flag=1;
		}

	}
	 
	int _GetFarthestDistance(Node* root,int& distance)
	{
		if(root==NULL)
			return 0;
		//后序遍历
		int left=_GetFarthestDistance(root->_left ,distance);
		int right=_GetFarthestDistance(root->_right ,distance);
		if(left+right>distance)  //更新distance
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