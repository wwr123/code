#pragma once
#include<iostream>
#include<cassert>
using namespace std;
enum Type
{
	HEAD_TYPE,
	VALUE_TYPE,
	SUB_TYPE,
};
struct GeneralizedNode
{
	Type _type;                     //����
	GeneralizedNode* _next;         //ָ��ͬ����һ���ڵ�
	union
	{
		char _value;
		GeneralizedNode* _subLink;  //ָ���ӱ��ָ��
	}; //��ʡ�ռ�
	GeneralizedNode(Type type,char value=0)
		:_type(type)
		,_next(0)
	{
		if(_type==VALUE_TYPE)
		{
			_value=value;
		}
		else if(_type==SUB_TYPE)
		{
			_subLink=NULL;
		}
	}
	GeneralizedNode()
	{}
};
class GeneralizedList
{
public:
	typedef GeneralizedNode Node;
	GeneralizedList()
		:_head(0)
	{}
	GeneralizedList(char* str)
		:_head(0)
	{
		_head=_GreateList(str);
	}
	GeneralizedList(const GeneralizedList& g)    //��������
	{
		_head=_Copy(g._head );
	}
	GeneralizedList& operator=(const GeneralizedList& g)
	{
		if(this!=&g)
		{
			GeneralizedList tmp(g);
			swap(_head,tmp._head );
		}
		return *this;
	}
	~GeneralizedList()
	{
		Node* cur=_head;
		while(cur)
		{
			Node* prev=cur;
			cur=cur->_next ;
			if(prev->_type ==SUB_TYPE)
			{
				_Destroy(prev->_subLink );
			}
			delete prev;
		}
	}
	void Print()
	{
		_Display(_head);
		cout<<endl;
	}
    void Size()
	{
		size_t count= _Size(_head);
		cout<<count<<endl;
	}
	void Depth()
	{
		size_t count=_Depth(_head);
		cout<<count<<endl;
	}
protected:
	void _Destroy(Node* head)
	{
		Node* cur=head;
		while(cur)
		{
			Node* prev=cur;
			cur=cur->_next;
			delete prev;
		}
	}
	Node* _Copy(Node* head)
	{
		Node* cur=head;
		Node* NewHead=new Node(*head);   //��������
		Node* prev=NewHead;
		cur=cur->_next ;
		while(cur)
		{
			Node* tmp=new Node(*cur);
			if(cur->_type ==SUB_TYPE)
			{
				tmp->_subLink =_Copy(cur->_subLink );
			}
			prev->_next =tmp;
			prev=tmp;
			cur=cur->_next ;
		}
		return NewHead;
	}
	size_t _Depth(Node* head)   //�����ӱ��б�������ȼ�1
	{
		if(head==NULL)
			return 1;     //���������Ϊ1
		Node* cur=head;
	    size_t max=0;
		while(cur)
		{
			size_t depth=0;
			if(cur->_type ==SUB_TYPE)
			{
				depth=_Depth(cur->_subLink );
			}
			if(max<depth)
				max=depth;
			cur=cur->_next ;
		}
		return max+1;
	}
	size_t _Size(Node* head)
	{
		Node* cur=head;
		size_t count=0;
		while(cur)
		{
			if(cur->_type ==VALUE_TYPE)
			{
				++count;
			}
			else if(cur->_type ==SUB_TYPE)
			{
				count+=_Size(cur->_subLink );
			}
			cur=cur->_next ;
		}
		return count;
	}
	void _Display(Node* head)
	{
		assert(head);
		Node* cur=head;
		while(cur)
		{
			if(cur->_type ==HEAD_TYPE)
			{
				cout<<"(";
			}
			if(cur->_type ==VALUE_TYPE)
			{
				cout<<cur->_value ;
			    if(cur->_next )
					cout<<",";
			}
			if(cur->_type ==SUB_TYPE)
			{
				_Display(cur->_subLink );
			    if(cur->_next )
					cout<<",";
			}
			cur=cur->_next ;
		}
		cout<<")";
	}

	bool _isvalue(char* str)
	{
		if((*str>='a'&&*str<='z')||(*str>='A'&&*str<='Z')||(*str>='0'&&*str<='9'))
			return true;
		else 
			return false;
	}
	
	Node* _GreateList(char*& str)   //�ݹ�
	{ 
		assert(*str=='(');
		++str;
		Node* head=new Node(HEAD_TYPE);
		Node* prev=head;
		while(str)
		{
			if(*str=='(')    //�ӱ�
			{
				Node* sub=new Node(SUB_TYPE);
				sub->_subLink =_GreateList(str);
				prev->_next =sub;
				prev=sub;
				++str;
			}
			else if(_isvalue(str))    //��ĸ
			{ 
				Node* node=new Node(VALUE_TYPE,*str);
				prev->_next =node;
				prev=node;
				++str;
			}
			else if(*str==')')
			{
				prev->_next =NULL;
				return head;
			}
			else
				++str;
		}
		return head;
	}
protected:
	Node* _head;
};
void TestGeneralizedList()
{
	char* a="(a,b,(c,d),(e,(f),h))";
	//char* a="(a,b,(c))";
	GeneralizedList gl(a);
	gl.Print ();
	GeneralizedList g2(gl);
	g2.Print ();
	GeneralizedList g3;
	g3=g2;
	g3.Print ();
	//gl.Print ();
	//gl.Size ();
	//gl.Depth ();
}