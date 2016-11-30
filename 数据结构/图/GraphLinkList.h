#pragma once
template<class V,class W>
class GraphLinkList
{
public:
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
{
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
	g.BFS ("����");
}