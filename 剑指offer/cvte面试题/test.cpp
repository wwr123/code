#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<string.h>
#include<stdio.h>
//求三个字符串中相同的元素，并统计他们总共出现的次数
void EqualElement(char* str1,char* str2,char* str3)
{
    int buf[256];
	int bufflag[256];
	memset(buf,0,sizeof(buf));
	memset(bufflag,0,sizeof(bufflag));
	while(*str1!='\0')
	{
		buf[*str1-'\0']++;    //ASCII值为下标
		bufflag[*str1-'\0']=1;
		str1++;
	}
	int flag=0;
	while(*str2!='\0')
	{
		if(buf[*str2-'\0']!=0)   //在两个字符串中都存在   并且标志为2
		{
			buf[*str2-'\0']++;
			bufflag[*str2-'\0']=2;
			flag=1;
		}
		str2++;
	}
	if(flag==0)
		return;
	flag=0;
	while(*str3!='\0')
	{
		if(buf[*str3]!=0&&bufflag[*str3]==2)
		{
			buf[*str3]++;
			bufflag[*str3]=3;
			flag=1;
		}
		str3++;
	}
	if(flag==0)
		return;
    for(int i=0;i<256;i++)
	{
		if(buf[i]!=0&&bufflag[i]==3)
		{
			char ch=i+'\0';
			cout<<ch<<endl;
			cout<<buf[i];
		}
	}
	cout<<endl;
}
//替换占位符
string FormatString(const string& str,int n,const vector<char>& arg,int m)
{
	string s;
	string s1;
	if(n>500)
		return s1;
	int i=0;
	int j=0;
	while(j<n)
	{
		if((str[j]>='a')&&(str[j]<='z')||(str[j]>='A'&&str[j]<='Z'))
		{
			s.push_back(str[j]);
		}
		else if(str[j]=='%')
		{
			int k=j+1;
			if(str[k]=='s')
			{
				if(i<m)
				{
					s.push_back(arg[i++]);
				    j++;
				}
				else
					return s1;
			}
			else
				return s1; 
		}
		else
			return s1;
		j++;
	}
	return s;
}
//求两个数组所有数中第K小的数  o(m+n)
int FindKNum(const vector<int>& arr1,const vector<int>& arr2,int kth)
{
	int i=0;
	int j=0;
	int count=0;
	int m=arr1.size();
	int n=arr2.size();
	if(kth>(arr1.size()+arr2.size()))
		return -1;
	while((i<m)&&j<n)
	{
		if(arr1[i]<=arr2[j])
		{
			count++;
			if(count==kth)
				return arr1[i];
			i++;
		}
		else if(arr1[i]>arr2[j])
		{
			count++;
			if(count==kth)
				return arr2[j];
			j++;
		}
	}
	if(i<arr1.size())
	{
		count++;
		if(count==kth)
			return arr1[i];
		i++;
	}
	if(j<arr2.size())
	{
		count++;
		if(count==kth)
			return arr2[j];
		j++;
	}
	return -1;
}
//优化方法 o(log(min(m,n)))
//二分查找
int FindKthNum(const vector<int>& arr1,const vector<int>& arr2,int kth)
{
	if((arr1.size()+arr2.size())<kth)
		return -1;
	if(kth<=arr1.size()&&arr1[kth-1]<arr2[0])
		return arr1[kth-1];
	if(kth<=arr2.size()&&arr2[kth-1]<arr1[0])
		return arr2[kth-1];
    if(kth>arr1.size()&&arr1[arr1.size()-1]<=arr2[0])
		return arr2[kth-arr1.size()-1];
    if(kth>arr2.size()&&arr2[arr2.size()-1]<=arr2[0])
		return arr1[kth-arr2.size()-1];

}

//出现超过一半的次数
#include<map>
int GetValue(const vector<int>& gifts,int n)
{
	map<int,int> m;
	for(int i=0;i<n;i++)
	{
		m[gifts[i]]++;
	}
	cout<<"end"<<endl;
	map<int,int>::iterator it=m.begin();
	int flag=0;
	while(it!=m.end())
	{
		if(((it->second)*2)>n)
		{
			flag=1;
			break;
		}
		it++;
	}
	if(flag==1)
		return it->first;
	else
		return -1;
}
int main()
{
	string str="A%sC%sE%s%s";
	vector<char> v;
	v.push_back('B');
	v.push_back('D');
	v.push_back('F');
	//string s=FormatString(str,11,v,v.size());
	//cout<<s<<endl;
	vector<int> arr1;
	arr1.push_back(1);
	arr1.push_back(2);
	arr1.push_back(3);
	arr1.push_back(4);
	vector<int> arr2;
	arr2.push_back(4);
	arr2.push_back(5);
	arr2.push_back(6);
	//int kth=FindKNum(arr1,arr2,5);
	//cout<<kth<<endl;
	//int m=GetValue(arr1,4);
	//cout<<m<<endl;
	char str1[]="adcb";
	char str2[]="afgd";
	char str3[]="dfgh";
	EqualElement(str1,str2,str3);
	return 0;
}
