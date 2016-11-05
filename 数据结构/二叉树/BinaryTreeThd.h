#include<iostream>
using namespace std;
#include<cstdlib>
#include<queue>
#include<stack>
#include<cassert>

enum PointerTag
{
	THREAD,
	LINK,
};
template<class T>
struct BinaryTreeThdNode
{
	T _data;
	BinaryTreeThdNode<T>* _letf;
	BinaryTreeThdNode<T>* _right; 
	PointerTag _letfTag; 
	PointerTag _rightTag; 
	BinaryTreeThdNode(const T& data)
		:_data(data)
		,_letf(NULL)
		,_right(NULL)
	{}
};
//实现中序遍历迭代器
template<class T,class Ref,class Ptr>
class BinaryTreeThdIterator
{
public:
	typedef BinaryTreeThdNode<T> Node;
	typedef BinaryTreeThdIterator<T,Ref,Ptr> Self;
	BinaryTreeThdIterator();
	BinaryTreeThdIterator(Node* node)
		:_node(node)
	{}
	Self& operator++()
	{
		Node* cur=_node;
		assert(cur);
		//找右子树的最左节点
		//1 的下一个节点是6
		if(cur->_rightTag ==LINK)
		{
			cur=cur->_right;
			while(cur&&cur->_letfTag ==LINK)
			{
				cur=cur->_letf ;
			}
			_node=cur;
		}
		else
			_node=cur->_right ;
		return *this;
	}
	/*Self operator++(int)
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}*/
	Self& operator--()
	{
		Node* cur=_node;
		assert(cur);
		//找左子树的最右节点
		//1 的前一个节点是4
		if(cur->_letfTag =LINK)
		{
			cur=cur->_letf ;
			while(cur&&cur->_rightTag ==LINK)
			{
				cur=cur->_right ;
			}
			_node=cur;
		}
		else
			_node=cur->_letf ;
		return *this;
	}
	T& operator*()
	{
		return _node->_data ;
	}
	bool operator!=(const Self& s)
	{
		return _node!=s._node ;
	}
private:
	Node* _node;
};
template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;
public:
	typedef BinaryTreeThdIterator<T,T&,T*> Iterator;
	BinaryTreeThd();
	BinaryTreeThd(const T* a,size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index=0;
		_root=_GreateTree(a,size,index,invalid);
	}
	void InorderThd()   //中序线索化
	{
		Node* prev=NULL;
		_InoderThd(_root,prev);
	}
	void prevorderThd()
	{
		Node* prev=NULL;
		_prevorderThd(_root,prev);
	}
	void PostOrderThd()
	{
		Node* prev=NULL;
		_PostOrderThd(_root,prev);
	}
	void prevorder()
	{
		_prevorder(_root);
		cout<<endl;
	}
	void Inorder()    //遍历
	{
		_Inorder(_root);
		cout<<endl;
	}
	void Postorder()
	{
		Node* cur=_root;
		Node* prev=NULL;
		while(cur)
		{
			//找最左边节点
			while(cur&&cur->_letfTag ==LINK)
			{
				cur=cur->_letf ;
			}
			//访问后继
			while(cur&&cur->_rightTag ==THREAD)
			{
				cout<<cur->_data <<" ";
				prev=cur;
			}
			
			cur=cur->_right ;
		}
	 }
     Iterator Begin()   //[
     {
			assert(_root);
			Node* root=_root;
			while(root&&root->_letfTag ==LINK)
			{
				root=root->_letf ;
			}
			return Iterator(root);
    }
	Iterator End()     //)
	{
		return Iterator(0);
	}
protected:
    void _PostOrderThd(Node* root,Node*& prev)
	{
		if(root==NULL)
			return;
		_PostOrderThd(root->_letf ,prev);
		_PostOrderThd(root->_right ,prev);

		if(root->_letf ==NULL)
		{
			root->_letfTag =THREAD;
			root->_letf =prev;
		}
		if(prev&&prev->_right ==NULL)
		{
			prev->_rightTag =THREAD;
			prev->_right =root;
		}
		prev=root;
	}

	void _prevorder(Node* root)
	{
		while(root)
		{
			while(root&&root->_letfTag ==LINK)
			{
				cout<<root->_data <<" ";
				root=root->_letf ;
			}
			cout<<root->_data <<" ";
			root=root->_right ;
		}
	}
    void _prevorderThd(Node* root,Node* &prev)
	{
		if(root==NULL)
			return;

		if(root->_letf ==NULL)
		{
			root->_letfTag =THREAD;
			root->_letf =prev;
		}
		
		if(prev&&(prev->_right ==NULL))
		{
			prev->_rightTag =THREAD;
			prev->_right =root;
		}

		prev=root;
		if(root->_letfTag ==LINK)
	 		_prevorderThd(root->_letf ,prev);
	
		if(root->_rightTag ==LINK)
			_prevorderThd(root->_right ,prev);
	}
	
	void _Inorder(Node* root)
	{
	     while(root)
		 {
			 //找左节点
			 while(root&&root->_letfTag==LINK)
			 {
				 root=root->_letf ;
			 }
			 cout<<root->_data <<" ";
			 //
			 while(root->_rightTag ==THREAD&&root->_right )
			 {
				 root=root->_right ;
				 cout<<root->_data <<" ";
			 }
			 root=root->_right ;
		 }
	}
	void _InoderThd(Node* root,Node* &prev)
	{
		if(root==NULL)
			return;
		_InoderThd(root->_letf ,prev);      //zuo

		if(root->_letf ==NULL)
		{
			root->_letfTag =THREAD;
			root->_letf =prev;
		}
		if(root->_right ==NULL)
			root->_rightTag =THREAD;
		if(prev&&prev->_rightTag ==THREAD)
			prev->_right =root;

		prev=root;

		_InoderThd(root->_right ,prev);      //you
	}
	Node* _GreateTree(const T *a,size_t size,size_t& index,const T& invalid)
	{
		Node* root=NULL;
		if(a[index]!=invalid&&index<size)
		{
			root=new Node(a[index]);
			root->_letfTag =LINK;
			root->_rightTag =LINK;
			root->_letf =_GreateTree(a,size,++index,invalid);
			root->_right =_GreateTree(a,size,++index,invalid);
		}
		return root;
	}
private:
	Node* _root;
};
void TestBinaryTreeThd()
{
	int a[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTreeThd<int> t(a,10,'#');
	t.InorderThd ();
	t.Inorder ();
	BinaryTreeThd<int>::Iterator it=t.Begin ();
	while(it!=t.End ())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	//t.prevorderThd ();
	//t.prevorder ();
	//t.PostOrderThd ();
}