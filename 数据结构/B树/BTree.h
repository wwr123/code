#pragma once
template<class K,int M>
struct BTreeNode
{
    K _keys[M];  
	BTreeNode<K,M>* _subs[M+1];
	BTreeNode<K,M>* _parent;
	size_t _size; //记录关键字的个数 
	BTreeNode()
		:_size(0)
		,_parent(NULL)
    {
		for(size_t i=0;i<M;++i)
		{
			_keys[i]=K();
			_subs[i]=NULL;
		}
		_subs[M]=NULL;
	}
};
template<class K,int M>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()
		:_root(new Node)
	{}
	bool Insert(const K& key)
	{
		if(_root->_size ==0)
		{
			_root->_keys [0]=key;
			_root->_size =1;
			return true;
		}
		//不是空树，找key是否存在
		pair<Node*,int> ret=Find(key);
		if(ret.second !=-1)  //找到
		{
			return false;
		}
		//没找到，需插入
		Node* cur=ret.first;
		K newkey=key;
		Node* sub=NULL;
		while(1)
		{
			//1.往cur中插入key
			//2.如果cur没满，停止，cur满了，继续调整
		 
			InsertKey(cur,newkey,sub);
			if(cur->_size <M)
				return true;

			//满了，分裂
			int mid=cur->_size /2;
			Node* tmp=new Node;
			size_t j=0;
			//新建一个节点，把右半边的key放到新建节点中
			for(size_t i=mid+1;i<cur->_size ;++i)
			{
				tmp->_keys [j++]=cur->_keys [i];
				tmp->_size ++;
				cur->_keys [i]=K();
			}
			j=0;
			//新建一个节点，把右半边的孩子节点放到新建节点中
			for(size_t i=mid+1;i<cur->_size +1;++i)
			{
				tmp->_subs [j]=cur->_subs [i];
				if(tmp->_subs [j])
					tmp->_subs [j]->_parent=tmp;
				++j;
				cur->_subs [i]=NULL;
			}


			//分裂的节点为根节点
			if(cur->_parent ==NULL)
			{
				_root=new Node;
				_root->_keys [0]=cur->_keys [mid];
				cur->_keys [mid]=K();
				_root->_size =1;
				_root->_subs [0]=cur;
				_root->_subs [1]=tmp;
				cur->_parent =_root;
				tmp->_parent =_root;
				cur->_size -=(tmp->_size +1);
				return true;
			}
			else
			{
				newkey=cur->_keys [mid];
				cur->_keys [mid]=K();
				sub=tmp;
				cur->_size =mid;
				cur=cur->_parent ;
			}

		}
	


	}
	void InsertKey(Node* cur,const K& key,Node* sub)
	{
		int i=cur->_size -1;
		while(i>=0)
		{
			if(cur->_keys [i]<key)
				break;
			else 
			{
				cur->_keys [i+1]=cur->_keys [i];
				cur->_subs [i+2]=cur->_subs [i+1];
			}
			--i;
		}
		cur->_keys [i+1]=key;
		cur->_subs [i+2]=sub;
		if(sub!=NULL)
			sub->_parent =cur;
	    cur->_size ++;
	}
	
	//找到返回TRUE，没找到返回他的父亲节点
	pair<Node*,int> Find(const K& key)
	{
		Node* cur=_root;
		Node* parent=cur;
		while(cur)
		{
			size_t i=0;
			while(i<cur->_size )
			{
				if(cur->_keys[i]<key)
					++i;
				else if(cur->_keys [i]>key) //访问孩子节点
				{
					break;
				}
				else  //找到key
					return pair<Node*,int> (cur,i);  //调用了匿名对象构造函数
 			} 
			parent=cur;
			cur=cur->_subs [i];
		} //cur为空
		return pair<Node*,int> (parent,-1);
	}

	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	void _InOrder(Node* root)
	{
		if(root==NULL)
			return;
		int i=0;
		for(i=0;i<root->_size;++i)
		{
			_InOrder(root->_subs [i]);
			cout<<root->_keys [i]<<" ";
		}
		_InOrder(root->_subs [i]);  //遍历最右边的孩子

	}
private:
	Node* _root;
};
void TestBTree()
{
	BTree<int,3> b;
	int arr[]={53,75,139,49,36,101};
	for(size_t i=0;i<sizeof(arr)/sizeof(arr[0]);++i)
	{
		b.Insert (arr[i]);
	}
	b.InOrder ();
}