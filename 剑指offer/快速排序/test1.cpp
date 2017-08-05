//快速排序
////左右指针法
int partsort(int* a,int start,int end)
{
	int key=a[end];
	int left=start;
	int right=end;
	while(left<right)
	{
		while((left<right)&&(a[left]<=key))
		{
			left++;
		}
		while((left<right)&&(a[right]>=key))
		{
			right--;
		}
		if(left<right)
		{
			swap(a[left],a[right]);
		}
	}
	swap(a[left],a[end]);
	return left;
	
}
//前后指针法 找比key小的，就停止
int partsort1(int* a,int start,int end)
{
	int cur=start;
	int prev=start-1;
	int key=a[end];
	while(cur<end)
	{
		if(a[cur]<key&&++prev!=cur)
			swap(a[prev],a[cur]);
		cur++;
	}
	prev++;
	swap(a[prev],a[end]);
	return prev;
}
//挖坑法  是左右指针法的变形
int partsort2(int* a,int start,int end)
{
	int key=a[end];
	int left=start;
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
void quicksort(int* a,int left,int right)
{
	cout<<"aa"<<endl;
	int pivo=partsort2(a,left,right);
	if((pivo+1)<right) //不止一个数
	{
		quicksort(a,pivo+1,right);
	}

	if(pivo>(left+1))
	{
		quicksort(a,left,pivo-1);
	}
}
