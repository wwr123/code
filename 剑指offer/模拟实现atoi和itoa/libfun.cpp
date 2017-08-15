#include<iostream>
using namespace std;
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<algorithm>
//数字前面右空格或tab会直接跳过，数组前面有字符直接返回0
//数字后面遇到不是数字的直接返回
int my_atoi(const char* ptr)
{
	assert(ptr);
	int num=0;
	while(isspace(*ptr))
		ptr++;
	while(*ptr!='\0')
	{
		if(*ptr>='0'&&*ptr<='9')
		{
			num=num*10+*ptr-'0';
			ptr++;
		}
		else 
			break;
	}
	return num;
}
//itoa函数是windows特有的，可以用sprintf函数模拟实现
char* my_itoa(int num,char* buf,int base)  //base为多少进制
{
	if(base==10)
		sprintf(buf,"%d",num);
	else if(base==8)
		sprintf(buf,"%o",num);
	else if(base==16)
		sprintf(buf,"%x",num);
	else if(base==2)
	{
		int i=0;
		while(num)
		{
		    if(num%2==1)	
				buf[i++]='1';
			else
				buf[i++]='0';
			num=num>>1;
		}
		buf[i]='\0';
		//反转字符串
		reverse(buf,buf+strlen(buf));
	}
	else
		return NULL;
	return buf;
}
//自已实现

char* my2_itoa(int num,char* buf,int base)
{
	char mm[17]="0123456789abcdef";
	char* str=buf;
	char tmp[100];
	int i=0;
	while(num)
	{
		tmp[i++]=mm[num%base];
		num=num/base;
	}
	int k=0;
	for(int j=i-1;j>=0;j--)
	{
		buf[k++]=tmp[j];
	}
	buf[k]='\0';
	return buf;
}
int main()
{
//    const char* str="abcd";
//	cout<<atoi(str)<<endl; //0
//	cout<<my_atoi(str)<<endl;
//
//	const char* str1="1234.67";
//	cout<<atoi(str1)<<endl; //1234
//	cout<<my_atoi(str1)<<endl;
//
//	const char* str2="	as1234.67";
//	cout<<atoi(str2)<<endl;  //0
//	cout<<my_atoi(str2)<<endl;
//
//	const char* str3="\n1234.67"; 
//	cout<<atoi(str3)<<endl;   //1234
//	cout<<my_atoi(str3)<<endl;
//
//	const char* str4="  	1234.67"; 
//	cout<<atoi(str4)<<endl;   //1234
//	cout<<my_atoi(str4)<<endl;
//
//	char ch='\n';
//	cout<<isspace(ch)<<endl;  //不是空白字符返回0，否则为非0

	char buf[33];
	int num=5;
	cout<<my2_itoa(num,buf,10)<<endl;
	cout<<my2_itoa(num,buf,8)<<endl;
	cout<<my2_itoa(num,buf,16)<<endl;
	cout<<my2_itoa(num,buf,2)<<endl;
	cout<<my2_itoa(num,buf,3)<<endl;
	return 0;
}
