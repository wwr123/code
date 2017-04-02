#include<stdio.h>
int main()
{
	//从小到大排序 合并
	int arr1[20]={1,3,5,8,10};
	int arr2[4]={2,6,8,9};
	int len1=5;
	int len2=4;
	int totellen=len1+len2-1;//合并后最后一个元素的下标
	int newlen=totellen;
	while(len1>0&&len2>0)
	{
		if(arr1[len1-1]<arr2[len2-1])
		{
			arr1[totellen--]=arr2[len2-1];
			len2--;
   
		}
		else
		{
			arr1[totellen--]=arr1[len1-1];
			len1--;
		}
	}
	if(len1==0)
	{
		while(len2>0)
		{	
			arr1[totellen--]=arr2[len2-1];
			len2--;
		}
	}
	int i=0;
	for(i=0;i<=newlen;++i)
	{
		printf("%d  ",arr1[i]);
	}
	printf("\n");
	return 0;
}
