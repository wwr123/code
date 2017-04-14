#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#define SIZE 1024 
int main()
{
	int data1=0;
	int data2=0;
	char* vec[3];
	char* ptr;
    char buf[SIZE];
    char* method=getenv("METHOD");
	if(strcasecmp(method,"GET")==0)
	{
		strcpy(buf,getenv("QUERRY"));
	}
	else
	{
    printf("method:%s",method);
    	char* content_len=getenv("CONTENT_LEN");
		int len=atoi(content_len);
		printf("content_len:%d",len);
		int i=0;
		for(i=0;i<len;++i)
		{
    	   char ch=0;
  	    	read(0,&ch,1);
			printf("c=%c",ch);
  	    	buf[i]=ch;
      	}
		buf[i]='\0';
	}

  printf("buf:%s",buf);
	ptr=buf;
	int i=0;
    while(*ptr)
	{
		if(*ptr=='=')
		{
			vec[i]=ptr+1;
			i++;
		}
		if(*ptr=='&')
			*ptr='\0';

		++ptr;
	}
	data1=atoi(vec[0]);
	data2=atoi(vec[1]);

	printf("data1+data2=%d<br/>",data1+data2);
	printf("data1-data2=%d<br/>",data1-data2);
	printf("data1*data2=%d<br/>",data1*data2);
	printf("data1/data2=%d<br/>",data1/data2);
	printf("data1%%data2=%d<br/>",data1%data2);

	return 0;
}
