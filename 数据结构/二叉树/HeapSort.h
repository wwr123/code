#include<iostream>
using namespace std;
#include<cstdlib>
#include<cassert>
//#include"Heap.h"

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
template<class T,class compare>
void _AdjustDown(T* a,size_t parent,size_t size)
{
		size_t child=parent*2+1;   //ָ����ڵ�
		while(child<size)
		{
			if((child<size-1)&&compare()(a[child],a[child+1]))
				++child;   //ָ���ҽڵ�
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
	//����
	assert(a);

		//�ҵ�����һ��Ҷ�ӽڵ�
    for(int i=(size-2)/2;i>=0;--i)
	{
	    //���µ���
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