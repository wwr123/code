#pragma once
#include"Heap.h"
template<class T>
struct HuffmanTreeNode
{
	T _weight;
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	HuffmanTreeNode(const T& x)
		:_weight(x)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}

};
template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}
	HuffmanTree(T* a,size_t size)
	{
		struct NodeLess
		{
			bool operator()(Node* l,Node* r) const
			{
				return l->_weight>r->_weight ;
			}
		};
		//建小堆
		Heap<Node*,NodeLess> MinHeap;
		for(size_t i=0;i<size;++i)
		{
			Node* node=new Node(a[i]);
			MinHeap.Push (node);
		}
		//构树
		while(MinHeap.size ()>1)
		{
			Node* left=MinHeap.Top ();
			MinHeap.Pop ();
			Node* right=MinHeap.Top ();
			MinHeap.Pop ();

			Node* parent=new Node(left->_weight +right->_weight );
			parent->_left =left;
			parent->_right =right;
			left->_parent =parent;
			right->_parent =parent;
			MinHeap.Push (parent);
		}
		_root=MinHeap.Top ();

	}
	HuffmanTree(T* a,size_t size,const T& invalid)
	{
		struct NodeLess
		{
			bool operator()(Node* l,Node* r) const
			{
				return l->_weight>r->_weight ;
			}
		};
		//建小堆
		Heap<Node*,NodeLess> MinHeap;
		for(size_t i=0;i<size;++i)
		{
			if(a[i]!=invalid)
			{
				Node* node=new Node(a[i]);
				MinHeap.Push (node);
			}	
		}
		//构树
		while(MinHeap.size ()>1)
		{
			Node* left=MinHeap.Top ();
			MinHeap.Pop ();
			Node* right=MinHeap.Top ();
			MinHeap.Pop ();

			Node* parent=new Node(left->_weight+right->_weight );
			parent->_left =left;
			parent->_right =right;
			left->_parent =parent;
			right->_parent =parent;
			MinHeap.Push (parent);
		}
		_root=MinHeap.Top ();
	}

	Node* GetRoot()
	{
		return _root;
	}
private:
	Node* _root;
};
void TestHuffmanTree()
{
	int a[]={3,2,1,4};
	HuffmanTree<int> h(a,4);
	
}