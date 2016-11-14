#include<iostream>
using namespace std;
#include<cstdlib>
#include<cassert>
#include<vector>

//仿函数==>函数对象
template<class T>
struct Up
{
	bool operator()(const T& m,const T& n)    //建大堆
	{
		return m<n;
	}
};
template<class T>
struct Down
{
	bool operator()(const T& m,const T& n)    //建小堆
	{
		return m>n;
	}
};
template<class T,class compare=Up<T>>   //默认是大堆
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
		//建堆
		//找第一个叶子节点
		for(int i=(size-2)/2;i>=0;--i)
		{
			//向下调整
			AdjustDown(i);
		}
	}
	void Push(const T& x)
	{
		_a.push_back (x);
		//向上调整
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
		size_t child=parent*2+1;   //指向左节点
		while(child<_a.size())
		{
			if((child<_a.size ()-1)&&compare()(_a[child],_a[child+1]))
				++child;   //指向右节点
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