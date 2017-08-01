//堆排序 从小到大 建大堆 
void downadjust(int* a,int len,int parent)
{
	int child=parent*2+1;
	while(child<len)
	{
		if((child+1)<len&&a[child]<a[child+1])
			child++;
		if(a[child]>a[parent])
			swap(a[child],a[parent]);
		parent=child;
		child=parent*2+1;
	}
}
//时间复杂度：2^k-1=n  k=logn  o(nlogn) 
void heapsort(int* a,int len)
{
	for(int i=(len-2)/2;i>=0;--i)
	{
		downadjust(a,len,i);
	}
	for(int i=len-1;i>0;i--)
	{
		swap(a[0],a[i]);
		downadjust(a,i,0); //为什么要向下调整，因为以接近有序
	}
}