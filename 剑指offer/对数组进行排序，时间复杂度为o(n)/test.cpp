/对数组进行排序，时间复杂读为o(n)
//一般最快的排序事件复杂度为o(nlogn),怎么才能实现o(n)的复杂度
//用空间换事件来实现
void hashsort(int* a,int len)
{
	//可以先遍历一遍，确定一个最大最小值
    int min=a[0];
	int max=a[0];
	for(int i=0;i<len;i++)
	{
		if(a[i]<min)
			min=a[i];
		if(a[i]>max)
			max=a[i];
	}
	int tmp_len=max-min+1;
	int* tmp=new int[tmp_len];
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<len;i++)
	{
		int index=a[i]-min;
		tmp[index]++;
	}
	int j=0;
	for(int i=0;i<tmp_len;i++)
	{
		while(tmp[i]!=0)
		{
			a[j++]=i+min;
			tmp[i]--;
		}
	}
}