//找出超过一半的数，o(n)
//采用多数投票的算法
int GetMostValue(const vector<int>& gifts,int n)
{
	int value=gifts[0];
	int count=1;
	for(int i=1;i<n;i++)
	{
		if(gifts[i]==value)
			count++;
		else
			count--;
		if(count==0)
		{
			value=gifts[i];
			count=1;
		}
	}
	count=0;
	for(int i=0;i<n;i++)
	{
		if(gifts[i]==value)
			count++;
	}
	if(count<n/2)
		return 0;
	else
		return value;
}