#include<iostream>
using namespace std;
#include<cstdlib>
#include<cassert>
#include<vector>

//�º���==>��������
template<class T>
struct Up
{
	bool operator()(const T& m,const T& n)    //�����
	{
		return m<n;
	}
};
template<class T>
struct Down
{
	bool operator()(const T& m,const T& n)    //��С��
	{
		return m>n;
	}
};
template<class T,class compare=Up<T>>   //Ĭ���Ǵ��
class Heap
{
public:
	Heap()
	{}
	Heap(T* a,size_t size)
	{
		assert(a);
		_a.reserve (size);
		for(size_t i=0;i<size;i++)
		{
			_a.push_back (a[i]);
		}
		//����
		//�ҵ�һ��Ҷ�ӽڵ�
		for(int i=(size-2)/2;i>=0;--i)
		{
			//���µ���
			AdjustDown(i);
		}
	}
	void Push(const T& x)
	{
		_a.push_back (x);
		//���ϵ���
		AdjustUp(_a.size ()-1);
	}
	void Pop()
	{
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back ();
		AdjustDown(0);
	}
	const T& Top()
	{
		return _a[0];
	}
	size_t size()
	{
		return _a.size ();
	}
protected:
	void AdjustUp(size_t child)
	{
		while(child>0)
		{
			size_t parent=(child-1)/2;
			if(compare()(_a[parent],_a[child]))
			{
				swap(_a[parent],_a[child]);
				child=parent;
			}
			else
				break;
		}
	}
	void AdjustDown(size_t parent)
	{
		size_t child=parent*2+1;   //ָ����ڵ�
		while(child<_a.size())
		{
			if((child<_a.size ()-1)&&compare()(_a[child],_a[child+1]))
				++child;   //ָ���ҽڵ�
			if(compare()(_a[parent],_a[child]))
			{
				swap(_a[parent],_a[child]);
				parent=child;
				child=parent*2+1;
			}
			else
				break;
		}
	}
protected:
	vector<T> _a;
};
void TeatHeap()
{
	int a[]={10,16,18,12,11,13,15,17,14,19};
	Heap<int,Down<int>>  h(a,10);
	h.Push (20);
	h.Pop ();
}