#include<iostream>
using namespace std;
#include<cstdlib>
#include<cassert>

//����������ת�������˫������

//���������� :�ڵ���ߵ����к��С�ڸýڵ� �ұȵ�ǰ��
//������������������ͱ���������
template<class T>
struct BSTreeNode
{
	BSTreeNode(const T& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}
	BSTreeNode<T>* _left;
	BSTreeNode<T>* _right;
	T _key;
};

template<class T>
class BSTree
{
	typedef BSTreeNode<T> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	bool InsertR(const T& key)
	{
		return _InsertR(_root,key);
	}
	bool Insert(const T& key)
	{
		//1.����
		//2.������
		//3.����
		
		//����
		if(_root==NULL)
		{
			_root=new Node(key);
			return true;
		}
		Node* cur=_root;
		Node* prev=cur;
		while(cur)
		{
			if(cur->_key >key)
			{
				prev=cur;
				cur=cur->_left ;
			}
		    else if(cur->_key <key)
			{
				prev=cur;
				cur=cur->_right ;
			}
			else //if(cur->_key ==key)
				return false;  //����
		}
		//������
		
		if(prev->_key >key)
		{
			cur=new Node(key);
		    prev->_left =cur;
		}
		else
		{
			cur=new Node(key);
		    prev->_right =cur;
		}
		return true;
	}
	bool Remove(const T& key)
	{
		if(_root==NULL)
			return false;
		Node* cur=_root;
		Node* parent=NULL;
		while(cur)
		{
			if(cur->_key <key)
			{
				parent=cur;
				cur=cur->_right ;
			}
				
			else if(cur->_key >key)
			{
				parent=cur;
				cur=cur->_left ;
			}
			else    //�ҵ�key,��ɾ��
			{
				if(cur->_left==NULL )   //��Ϊ��
				{
					if(_root==cur)
					{
						_root=cur->_right ;
					}
					else if(parent->_left ==cur)
					{
						parent->_left =cur->_right ;
					}
					else
					{
						parent->_right =cur->_right ;
					}
					delete cur;
				}
				else if(cur->_right ==NULL)  //��Ϊ��
				{
					if(_root==cur)
					{
						_root=cur->_left ;
					}
					else if(parent->_left ==cur)
					{
						parent->_left =cur->_left ;
				    }
					else
					{
						parent->_right =cur->_left ;
					}
					delete cur;
				}
				else    //ɾ���Ľڵ����Ҷ���Ϊ��
				{
					//��������������ڵ�
					Node* righttree=cur->_right ;
					parent=cur;
					while(righttree->_left )
					{
						parent=righttree;
						righttree=righttree->_left ;
					}
					if(parent->_left ==righttree)
					{
						parent->_left =righttree->_right ;
					}
					else
					{
						parent->_right =righttree->_right ;
					}
				}
				return true;
			}
		}
		return false;
	}
	bool RemoveR(const T& key)
	{
		
	    return _RemoveR(_root,key);
	}
	bool Find(const T& key)
	{
		Node* cur=_root;
		while(cur)
		{
			if(cur->_key <key)
			{
				cur=cur->_right ;
			}
			else if(cur->_key >key)
			{
				cur=cur->_left ;
			}
			else if(cur->_key ==key)
				return true;	
		}
		return false;
	}
	bool FindR(const T& key)
	{
		_FindR(_root,key);
	}
	void InOrderR()
	{
		_InOrderR(_root);
		cout<<endl;
	}
	Node* TreeToList()
	{
		if(_root==NULL)
			return NULL;
		Node* prev=NULL;
		_ToList(_root,prev);
		while(_root->_left )
		{
			_root=_root->_left ;
		}
		return _root;
	}
protected:
	void _ToList(Node* root,Node*& prev)
	{
		if(root==NULL)
			return;
		_ToList(root->_left ,prev);
		root->_left=prev;
		if(prev)
		{
			prev->_right =root;
		}
		prev=root;
		_ToList(root->_right ,prev);
	}
	bool _FindR(Node* root,const T& key)
	{
		if(root==NULL)
			return false;
		if(root->_key >key)
		    return _FindR(root->_left ,key);
		else if(root->_key <key)
			return _FindR(root->_right ,key);
		else
			return true;
	}
	bool _RemoveR(Node*& root,const T& key)//&������ص�
	{
		if(root==NULL)
			return false;
		if(root->_key <key)
			return _RemoveR(root->_right ,key);
		else if(root->_key >key)
		    return _RemoveR(root->_left ,key);
		else    //�ҵ�����ɾ��
		{
			Node* del=root;
			if(root->_left ==NULL)
			{
				root=root->_right ;
			}
			else
			{
				root=root->_left ;
			}
			delete del;
		}
	}
	void _InOrderR(Node* root)
	{
		if(root==NULL)
		return;
	   _InOrderR(root->_left );
	   cout<<root->_key<<" " ;
	   _InOrderR(root->_right );
	}
	
	bool _InsertR(Node*& root,const T& key)
	{
		if(root==NULL)
		{
			root=new Node(key);
			return true;
		}
		if(root->_key>key)
		{
			return _InsertR(root->_left ,key);
		}
		else if(root->_key <key)
		{
			return _InsertR(root->_right ,key);
		}
		else  //���������root->_key==key
		{
			return false;
		}

	}
private:
	Node* _root;
};
void TestBSTree()
{
	BSTree<int> t;
	t.InsertR (6);
	t.InsertR (5);
	t.InsertR (11);
	t.InsertR (9);
	t.InsertR (10);
    //cout<<t.RemoveR (5);  //1
	//t.InOrderR ();    //5 6 9 10 11
	//t.RemoveR (5);
	//t.RemoveR (6);
	//t.RemoveR (11);
	//t.RemoveR (9);
	//t.RemoveR (10);
	//t.InOrderR ();
	cout<<t.Find (9)<<endl;   //1
	//cout<<t.Find (3)<<endl;   //0
	//t.Remove (6);   
	//t.InOrderR ();  //5 9 10 11//
	//cout<<t.TreeToList ();
	
}



