//归并排序 空间复杂度为o(nlogn)
//把排序好的数放到新开，最后在拷回到原来的数组中
//递归排，采用分治的思想
void mergesortR(int* a,int* tmp,int start,int end)
{
	int mid=start+(end-start)/2;
	if(mid>start) 
	{
		mergesortR(a,tmp,start,mid);
	}
	if(mid+1<end)
	{
		mergesortR(a,tmp,mid+1,end);
	}
	int start1=start;
	int end1=mid;
	int start2=mid+1;
	int end2=end;
	int index=start; //控制tmp的下标
	//排序
	while(start1<=end1&&start2<=end2) //两部分都不能越界了
	{
		if(a[start1]<a[start2])
			tmp[index++]=a[start1++];
		else
			tmp[index++]=a[start2++];
	}
    while(start1<=end1)
	{
		tmp[index++]=a[start1++];
	}
	while(start2<=end2)
	{
		tmp[index++]=a[start2++];
	}
	//把已经有序的数组拷回到原来的数组中
	for(int i=start;i<=end;i++)
	{
		a[i]=tmp[i];	
	}
}
void mergesort(int* a,int len)
{
	int* tmp=new int[len];
	mergesortR(a,tmp,0,len-1);
}
