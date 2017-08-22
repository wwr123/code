#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#define SIZE 1024
#include"mysql_op.h"
#include<iostream>
using namespace std;
#include<string>

int main()
{
	int data1=0;
	int data2=0;
	char* vec[3];
	char* ptr;
    char buf[SIZE];  //保存的是参数
    char* method=getenv("METHOD");
	if(strcasecmp(method,"GET")==0)
	{
		strcpy(buf,getenv("QUERRY"));
	}
	else
	{
    	char* content_len=getenv("CONTENT_LEN");
		int len=atoi(content_len);
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

	ptr=buf;
	int i=0;
    while(*ptr!='\0')
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

//没加数据库的代码
//data1=atoi(vec[0]);
//data2=atoi(vec[1]);
//printf("data1+data2=%d<br/>",data1+data2);
//printf("data1-data2=%d<br/>",data1-data2);
//printf("data1*data2=%d<br/>",data1*data2);
//printf("data1/data2=%d<br/>",data1/data2);
//printf("data1%%data2=%d<br/>",data1%data2);

    //加数据库
	MysqlOp db;
	db.SetConnect("127.0.0.1","root","root","mywwr");
	string s;
	s="INSERT INTO student(name,sex) VALUES('";
	s+=vec[0];
	s+="','";
	s+=vec[1];
	s+="')";
	if(db.Insert(s.c_str())==false)
	{
		return 1;
	}
	else //插入成功
	{
		printf("name=%s,sex=%s<br/>",vec[0],vec[1]);
	}
//	if(db.Insert("INSERT INTO student(name,sex) VALUES('xiaoer','nv')")==false)
//	{
//		return 2;
//	}
//	if(db.Delete("DELETE FROM student where id=1")==false)
//	{
//		return 3;
//	}
//	  cout<<"update start"<<endl;
//	if(db.Update("UPDATE student SET name='zhang' where id=5")==false)
//	{
//		return 3;
//	  }
//	cout<<"update end"<<endl;
    s="SELECT * FROM student";
	if(db.Select(s.c_str())==false)
	{
		return false;
	}
	return 0;
}
