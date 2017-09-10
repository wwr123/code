//最长公共子串
void Lsc()
{
	string s1="abcde";
	string s2="bebcd";
	int max=0;
	int end=0;
	int row=0;
	int col=s2.size()-1;
	int length=s1.size();
	while(row < length)
	{
		//开始向右下方遍历
		int i=row;
		int j=col;
		int len=0;
		while(i< s1.size()&&j< s2.size())
		{
			if(s1[i]!=s2[j])
			{
				len=0;
			}
			else 
			{
				len++;
			}
			if(max<len)
			{
				max=len;
				end=i;
			}
			//cout<<s1[i]<<" "<<s2[j]<<endl;
			//cout<<len<<endl;
			i++;
			j++;
		}
		if(col>0)
			col--;
		else
			row++;
	}
	for(int i=end-max+1;i<=end;i++)
	{
		cout<<s1[i];
	}
	cout<<endl;
}