#include<iostream>
using namespace std;
#include<cstdlib>
#include<cassert>
//#include"Heap.h"

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
template<class T,class compare>
void _AdjustDown(T* a,size_t parent,size_t size)
{
		size_t child=parent*2+1;   //指向左节点
		while(child<size)
		{
			if((child<size-1)&&compare()(a[child],a[child+1]))
				++child;   //指向右节点
			if(compare()(a[parent],a[child]))
			{
				swap(a[parent],a[child]);
				parent=child;
				child=parent*2+1;
			}
			else
				break;
		}
}
template<class T>
void HeapSort(T* a,size_t size)
{
	//建堆
	assert(a);

		//找倒数第一个叶子节点
    for(int i=(size-2)/2;i>=0;--i)
	{
	    //向下调整
	     _AdjustDown<T,Down<T>>(a,i,10);
    }
	size_t End=size;
	while(End>0)
    {
		swap(a[0],a[End-1]);
		--End;
		_AdjustDown<int,Down<int>>(a,0,End);
	}
	
}
void TestHeapSort()
{
	int a[]={10,16,18,12,11,13,15,17,14,19};
	HeapSort(a,10);

}