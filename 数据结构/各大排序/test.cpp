#include<iostream>
using namespace std;
#include<cstdlib>
#include<stack>
#include<windows.h>
void InsertSort(int* a,size_t n)  //按升序
{
	for(size_t index=1;index<n;++index)
	{
		int pos=index-1;
		int tmp=a[index];
		while(pos>=0&&a[pos]>tmp)
		{
			a[pos+1]=a[pos];
			--pos;
		}
		a[pos+1]=tmp;
	}
}
void ShellSort(int* a,size_t n)
{
	//1.预排序
	int gap=n;
	while(gap>1)
	{
		gap=gap/3+1;  
		for(int index=gap;index<n;++index)
		{
		    int tmp=a[index];
			int pos=index-gap;
			while(pos>=0&&a[pos]>tmp)
			{
				a[pos+gap]=a[pos];
				pos-=gap;
			}
			a[pos+gap]=tmp;
		}
		
	}
	//2.插入排序
	InsertSort(a,n);
	
}
void SelectSort(int* a,size_t n)
{
	int left=0;
	int right=n-1;
	int min,max;
	while(left<right)
	{
		min=max=left;
		for(size_t i=left;i<=right;++i)
		{
			if(a[i]<a[min])
				min=i;
			if(a[i]>a[max])
				max=i;
		}
		swap(a[left],a[min]);
		if(left==max)
			max=min;
		swap(a[right],a[max]);
		left++;
		--right;
	}
}
//三数取中法
int GetMidNum(int* a,int begin,int end)
{
	int mid=begin+(end-begin)/2;
	if(a[begin]>a[mid])
	{
		if(a[mid]>a[end])
			return mid;
		else
		{
			if(a[begin]>a[end])
				return end;
			else
				return begin;
		}
	}
	else
	{
		if(a[mid]<a[end])
			return mid;
		else
		{
			if(a[begin]>a[end])
				return begin;
			else
				return end;
		}
	}
}
//左右指针法
int PartSort1(int* a,int begin,int end)
{
	int left=begin;
	int right=end;
	//int key=a[end];

	//三数取中法
	int mid=GetMidNum(a,begin,end);
	swap(a[mid],a[end]);
	int key=a[end];

	while(left<right)
	{
		while(left<right&&a[left]<=key)
			left++;
		while(left<right&&a[right]>=key)
			right--;
		if(left<right)
			swap(a[left],a[right]);
	}
	swap(a[left],a[end]);
	return left;
}
//挖坑法
int PartSort2(int* a,int begin,int end)
{
	//int key=a[end];

	//三数取中法
	int mid=GetMidNum(a,begin,end);
	swap(a[mid],a[end]);
	int key=a[end];

	int left=begin;
	int right=end;
	while(left<right)
	{
		while(left<right&&a[left]<=key)
			left++;
		a[right]=a[left];
		while(left<right&&a[right]>=key)
			right--;
		a[left]=a[right];
	}
	a[left]=key;
	return left;
}
//前后指针法
int PartSort3(int* a,int begin,int end)
{
	int prev=begin-1;
	int cur=begin;//找比key小的值就停下
	int mid=GetMidNum(a,begin,end);
	swap(a[mid],a[end]);
	int key=a[end];
	while(cur<end)
	{
		if(a[cur]<key&&++prev!=cur)
			swap(a[prev],a[cur]);
		++cur;
	}
	swap(a[++prev],a[end]);
	return prev;
}
void QuickSortNonR(int* a,int begin,int end)
{
	stack<int> s;
	s.push (begin);
	s.push (end);
	while(!s.empty ())
	{
		int right=s.top ();
		s.pop();
		int left=s.top();
		s.pop();
		int pivo=PartSort1(a,left,right);
		if(left<pivo-1)//不止一个数
		{
			s.push(left);
			s.push(pivo-1);
		}
		if(pivo+1<end)
		{
			s.push(pivo+1);
			s.push(end);
		}
	}
}
void QuickSort(int* a,int begin,int end)
{
	//一趟排序
	//int pivo=PartSort1(a,begin,end);
	//int pivo=PartSort2(a,begin,end);
	int pivo=PartSort3(a,begin,end);

	if(begin<pivo-1)  //不止一个数
		QuickSort(a,begin,pivo-1);
	if(pivo+1<end)
		QuickSort(a,pivo+1,end);
}
void QuickSort2(int* a,int begin,int end)
{
	//一趟排序
	//int pivo=PartSort1(a,begin,end);
	//int pivo=PartSort2(a,begin,end);
	int pivo=PartSort3(a,begin,end);
	if(end-begin>13)
	{
		if(begin<pivo-1)  //不止一个数
			QuickSort(a,begin,pivo-1);
	    if(pivo+1<end)
		    QuickSort(a,pivo+1,end);
	}
	else
	{
		InsertSort(a+begin,end-begin);
	}
}
void _MergeSort(int* a,int* tmp,int begin,int end)
{
	int mid=begin+(end-begin)/2;
	if(begin<mid)  //不止一个数
	{
		_MergeSort(a,tmp,begin,mid);
	}
	if(mid+1<end)
	{
		_MergeSort(a,tmp,mid+1,end);
	}

	int begin1=begin;
	int end1=mid;
	int begin2=mid+1;
	int end2=end;
	int index=begin;
	while(begin1<=end1&&begin2<=end2)   //两个数组都不为空
	{
		if(a[begin1]<a[begin2])
			tmp[index++]=a[begin1++];
		else
			tmp[index++]=a[begin2++];
	}
	while(begin1<=end1)  //不为空
	{
		tmp[index++]=a[begin1++];
	}
	while(begin2<=end2)  //不为空
	{
		tmp[index++]=a[begin2++];
	}
	for(size_t i=begin;i<=end;++i)
	{
		a[i]=tmp[i];
	}
}
void MergeSort(int* a,size_t n)
{
	int* tmp=new int[n];
	_MergeSort(a,tmp,0,n-1);
	delete[] tmp;
}
void AdjustDown(int* a,int parent,size_t n)  //建大堆
{
	int sub=parent*2+1;
	while(sub<n)
	{
		if(sub<n-1&&a[sub]<a[sub+1])
		     ++sub;
		if(a[sub]>a[parent])
		{
			swap(a[sub],a[parent]);
	        parent=sub;
            sub=parent*2+1;
		}
		else
			break;
	}
}
void HeapSort(int* a,size_t n)
{
	//建大（小）堆
	for(int i=(n-2)/2;i>=0;--i)
	{
		AdjustDown(a,i,n);
	}
	//排序
	for(int j=n-1;j>0;--j)
	{
		swap(a[0],a[j]);
		AdjustDown(a,0,j);
	}
}
void TestSort()
{
	int a[]={5,0,6,2,3,8,1,9};
	int n=sizeof(a)/sizeof(a[0]);
	//InsertSort(a,n);
	//ShellSort(a,n);
	//SelectSort(a,n);
	//QuickSort(a,0,n-1);
	//QuickSortNonR(a,0,n-1);
    //MergeSort(a,n);
	HeapSort(a,n);
	for(size_t i=0;i<n;++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
	//测试快速排序中，当数组中的个数小于13时，用递归写法快排的效率小于插入排序
	//const int N=10000;
	//int a[N];
	//int b[N];
	//int c[N];
	//for(size_t i=0;i<N;++i)
	//{
	//	a[i]=b[i]=c[i]=i;
	//}

	//int start=GetTickCount();
	//QuickSort(a,0,N-1);
	//int end=GetTickCount();
	//cout<<end-start<<endl;   //16

	//start=GetTickCount();
	//QuickSort2(b,0,N-1);
	//end=GetTickCount();
	//cout<<end-start<<endl;  //15

	//int start=GetTickCount();
	//QuickSortNonR(c,0,N-1);
	//int end=GetTickCount();
	//cout<<end-start<<endl;  //特别慢

}
int main()
{
	TestSort();
	system("pause");
	return 0;
}