#include<stdio.h>
#include<string.h>
//替换空格--》%20
#define MAX 50
int main()
{
	char str[MAX]=" we  are happy ";
	int len=strlen(str);
	//遍历一遍，求出空格的个数O（n）
	int i=0;
	int count=0;
	for(i=0;i<len;++i)
	{
		if(str[i]==' ')
			count++;
	}
	//从后向前替换
	char *p1=str+len;//指向最后的\0
	char *p2=str+len+2*count;
	while(len>=0) //p1<=p2
	{
		if(*p1!=' ')
		{
			*p2=*p1;
			--p1;
			--p2;
			--len;
		}
		else
		{
			--p1;
			--len;
		    *p2='0';
			--p2;
			*p2='2';
			--p2;
			*p2='%';
			--p2;
		}
	}
    printf("%s\n",str);
	return 0;
}
