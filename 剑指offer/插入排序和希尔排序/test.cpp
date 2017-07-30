#include<iostream>
using namespace std;

//选择排序 从小到大
//一趟排序选择出一个最小的数与第一个位置的数进行替换，依次类推
void selectsort(int *a,int len)
{
	if(a==NULL||len<=0)
		return;
	int min=0;
	int max=0;
	for(int i=0;i<len/2;++i)
	{
		for(int j=i;j<len-i;++j)
		{
			if(a[j]>a[max])
			{
				max=j;
			}
			if(a[j]<a[min])
			{
				min=j;
			}
		}
		if(max==i&&min!=(len-i-i))
		{
			swap(a[len-1-i],a[max]);
		    swap(a[i],a[min]);
		}
		else if(max==i&&min==(len-i-1))
			swap(a[min],a[max]);
		else
		{
			swap(a[i],a[min]);
			swap(a[len-1-i],a[max]);
		}
	}
}
//希尔排序是基于插入排序的一种，比插入排序快，每次选择一个增量，然后直接进行插入排序
//希尔：n/2,n/4,...1   o(nlogn)
//插入:1,2,3,..n-1,n

void insertsort(int *a,int len)
{
	for(int i=1;i<len;i++)
	{
		for(int j=i-1;j>=0&&a[j+1]<a[j];--j)
		{
			swap(a[j],a[j+1]);
		}
	}
}
void shellsort(int *a,int len)
{
	for(int i=len/2;i>1;i=i/2) //每次的增量，直到为1
	{
		for(int j=0;j<i;j++)  //交换排序
		{
			for(int k=j;k<len;k+=i)
			{
				if(a[k]>a[k+i]&&(k+i)<len) //判断这一位和他要交换的下一个位置的数时，需要判断下一位是否存在
					swap(a[k],a[k+i]);
			}
		}
	}
	//当增量为1时，直接进行插入排序
	insertsort(a,len);
}
void fun()
{
	int a[]={4,5,3,9,2};
	int len=sizeof(a)/sizeof(a[0]);
	//selectsort(a,len);
	shellsort(a,len);
	for(int i=0;i<len;++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	fun();
	return 0;
}