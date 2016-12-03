//计数排序
void CountSort(int* a,size_t n)
{
	int max=a[0];
	int min=a[0];
	for(size_t i=0;i<n;++i)
	{
		if(a[i]>max)
			max=a[i];
		if(a[i]<min)
			min=a[i];
	}
	int range=max-min+1;
	int* tmp=new int[range];
	memset(tmp,0,sizeof(int)*range);
	for(size_t i=0;i<n;++i)
	{
		tmp[a[i]-min]++;
	}
	int index=0;
	for(size_t i=0;i<range;++i)
	{
		while(tmp[i]--)
		{
			a[index++]=i+min;
		}
	}
}
//基数排序
int GetMaxDigit(int* a,size_t n)
{
	int max=1;
	int base=10;
	for(size_t i=0;i<n;++i)
	{
		while(a[i]/base)
		{
			max++;
			base*=10;
		}
	}
	return max;
}
void LSD(int* a,size_t n)
{
	int count[10]={0};   //统计出现的次数
	int start[10]={0};   //第一次出现的位置
	int* tmp=new int[n];


	int max= GetMaxDigit(a,n);
	int base=1;
	for(size_t i=0;i<max;++i)
	{
		for(size_t i=0;i<n;++i)
		{
			count[(a[i]/base)%10]++;
		}

		start[0]=0;
		for(size_t i=1;i<10;++i)
		{
			start[i]=count[i-1]+start[i-1];
		}

		//排序
		for(size_t i=0;i<n;++i)
		{
			int num=(a[i]/base)%10;
			tmp[start[num]++]=a[i];
		}
		memcpy(a,tmp,sizeof(int)*n);
		base*=10;
	}
	
}