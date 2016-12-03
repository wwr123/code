#pragma once
#include<cassert>
template<class V,class W>
class GraphLinkList
{
public:
	GraphLinkList(){}
	GraphLinkList(V* vertex,size_t size,bool isHaveDirecte=false)
		:_isHaveDirecte(isHaveDirecte)
		,_vertex(vertex,vertex+size)
	{
		_tables.resize(size);
	}
	int GetIndex(const V& v)
	{
		for(size_t i=0;i<_vertex.size();++i)
		{
			if(_vertex[i]==v)
				return i;
		}
		throw std::invalid_argument("��������");
	}
	void AddEdge(const V& v1,const V& v2,const W& w)
	{
		int index1=GetIndex(v1);
		int index2=GetIndex(v2);
		_AddEdge(index1,index2,w);
	}

	void _AddEdge(int index1,int index2,const W& w)
	{
		Node* tmp=new Node(index1,index2,w);
		//ͷ��
		tmp->_next=_tables[index1];
		_tables[index1]=tmp;
		if(_isHaveDirecte==false)
		{
			Node* tmp2=new Node(index2,index1,w);
			tmp2->_next=_tables[index2];
			_tables[index2]=tmp2;
		}
	}
	void Print()
	{
		for(size_t i=0;i<_tables.size();++i)
		{
			Node* cur=_tables[i];
			cout<<_vertex[i]<<"::";
			while(cur)
			{
				cout<<_vertex[cur->_index2]<<":"<<cur->_w<<"->";
				cur=cur->_next;
			}
			cout<<"NULL"<<endl;
		}
	}
	//�������
	void DFS(const V& v)
	{
		size_t index=GetIndex(v);
		vector<bool> state(_vertex.size(),false);
		_DFS(index,state);
	}
	void _DFS(size_t index,vector<bool>& state)
	{
		cout<<_vertex[index]<<"->";
		state[index]=true;
        Node* cur=_tables[index];
		while(cur)
		{
			if(state[cur->_index2]==false)
			{
				_DFS(cur->_index2,state);
			}
			cur=cur->_next;
		}
	}
	//�������
	void BFS(const V& v)
	{
		size_t index=GetIndex(v);
		vector<bool> state(_vertex.size(),false);
		queue<int> q;
		q.push (index);
		while(!q.empty())
		{
			int front=q.front ();
			q.pop();
			if(state[front]==false)
			{
				cout<<_vertex[front]<<"->";
				state[front]=true;
			}
			Node* cur=_tables[front];
			while(cur)
			{
				if(state[cur->_index2]==false)
				{
					cout<<_vertex[cur->_index2]<<"->";
					q.push (cur->_index2);
					state[cur->_index2]=true;
				}
				cur=cur->_next;
			}
		}
	}

	//��С������
	bool KruskalGetMinTree(GraphLinkList<V,W>& minTree)
	{
		//��ʼ��
		assert(_isHaveDirecte==false);
		minTree._vertex =_vertex;
		minTree._tables .resize(_tables.size());
		minTree._isHaveDirecte =_isHaveDirecte;

		//��С��
		struct Compare
		{
			bool operator()(Node* m,Node* n)    //��С��
			{
				return m->_w>n->_w;
			}
		};
		Heap<Node*,Compare> minHeap;

		//�ѱߣ��ڵ㣩�ӵ�����
		for(size_t i=0;i<_tables.size();++i)
		{
			Node* cur=_tables[i];
			//��һ���¶��ڵ㣬��������С������
			if(cur==NULL)
				return false;

			while(cur)
			{
				minHeap.Push(cur);
				cur=cur->_next;
			}
		}

		//ѡ��n-1����
		UnionFindSet u(_vertex.size());
		size_t n=0;
		while(n<_vertex.size()-1)
		{
			Node* cur=minHeap.Top();
			int root1=u.FindRoot (cur->_index1);
			int root2=u.FindRoot (cur->_index2);
			if(root1!=root2)   //����һ�������У����ṹ�ɻ�·
			{
				minTree._AddEdge(cur->_index1,cur->_index2,cur->_w);
				u.Union (root1,root2);
				n++;
			}
			minHeap.Pop();
		}
			
		if(n==_vertex.size()-1)
			return true;
		else
			return false;

	}
	~GraphLinkList()
	{
		for(size_t i=0;i<_tables.size();++i)
		{
			Node* cur=_tables[i];
			while(cur)
			{
				Node* del=cur;
				cur=cur->_next;
				delete del;
				del=NULL;
			}
		}
	}
protected:
	struct Node
	{
		W _w;
		size_t _index1; //�����Ӧ���±�
		size_t _index2; //�����Ӧ���±�
		Node* _next;
		Node(size_t index1,size_t index2,const W& w)
			:_index1(index1)
            ,_index2(index2)
			,_w(w)
			,_next(NULL)
		{}
	};
	vector<V> _vertex;
	vector<Node*> _tables;
	bool _isHaveDirecte;
};
void TestGraphLinkList()
{/*
	string v[5]={"����","���","�Ϻ�","����","�㶫"};
	GraphLinkList<string,int> g(v,5);
	g.AddEdge ("����","���",200);
	g.AddEdge ("����","�Ϻ�",500);
	g.AddEdge ("�㶫","�Ϻ�",500);
	g.AddEdge ("���","����",100);
	g.AddEdge ("����","���",300);
	g.AddEdge ("�㶫","����",100);
	g.Print ();
	g.DFS ("����");
	cout<<endl;
	g.BFS ("����");*/
	int v[5]={0,1,2,3,4};
	GraphLinkList<int,int> g(v,5);
	g.AddEdge (1,2,10);
	g.AddEdge (1,3,20);
	g.AddEdge (1,4,30);
	g.AddEdge (2,4,40);
	//g.AddEdge (4,0,20);
	//g.AddEdge (0,3,10);
	GraphLinkList<int,int> gl;
	cout<<g.KruskalGetMinTree (gl)<<endl;
}