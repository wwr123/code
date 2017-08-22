#include"mysql_op.h"
#include<cstring>

bool MysqlOp::SetConnect(const char* host,const char* user,
		const char* passwd,const char* mysql_name)
{
	//初始化
	conn=mysql_init(NULL);
	if(conn==NULL)
	{
		cout<<"mysql_init faild"<<endl;
		return false;
	}
	//创建连接
	if((conn=mysql_real_connect(conn,host,user,passwd,mysql_name,0,NULL,0))==NULL)
	{
		cout<<"mysql_real_connect faild"<<endl;
		return false;
	}
	return true;
}
bool MysqlOp::Insert(const char* info)
{
	if(strncasecmp("INSERT INTO ",info,strlen("INSERT INTO "))!=0)
	{
		cout<<"参数错误"<<endl;
		return false;
	}
	//执行info里面的语句
	if(mysql_real_query(conn,info,strlen(info))!=0)
	{
		cout<<"mysql_real_query faild"<<endl;
		return false;
	}
    return true;
}
bool MysqlOp::Delete(const char* info)
{
	if(strncasecmp("DELETE FROM ",info,strlen("DELETE FROM "))!=0)
	{
		cout<<"参数错误"<<endl;
		return false;
	}
	if(mysql_real_query(conn,info,strlen(info))!=0)
	{
		cout<<"mysql_real_query faild"<<endl;
		return false;
	}
    return true;
}
bool MysqlOp::Update(const char* info)
{
	if(strncasecmp("UPDATE ",info,strlen("UPDATE "))!=0)
	{
		cout<<"参数错误"<<endl;
		return false;
	}
	if(mysql_real_query(conn,info,strlen(info))!=0)
	{
		cout<<"mysql_real_query faild"<<endl;
    	return true;
	}
	return true;
}
bool MysqlOp::Select(const char* info)
{
	if(strncasecmp("SELECT * FROM ",info,strlen("SELECT * FROM "))!=0)
	{
		cout<<"参数错误"<<endl;
		return false;
	}
	//要先执行这个命令，才能获取信息
	if(mysql_real_query(conn,info,strlen(info))!=0)
	{
		cout<<"mysql_real_query faild"<<endl;
		return false;
	}
	MYSQL_RES* result;
	//获取数据库的信息，返回到result
	if((result=mysql_store_result(conn))==NULL)
	{
		cout<<"mysql_store_result faild"<<endl;
		return false;
	}
    //获得行数
	int rows=mysql_num_rows(result);
	//获得列数
	int fields=mysql_num_fields(result);
	//检索列字段的定义,打印出每一列的名字
	MYSQL_FIELD* f=NULL;
	for(int i=0;i<fields;++i)
	{
		f=mysql_fetch_field_direct(result,i);
		cout<<f->name<<"  ";
	}
	cout<<"<br/>"<<endl;
	//按行读取结果集（result）的内容
	MYSQL_ROW row=NULL;
	while(row=mysql_fetch_row(result))
	{
		for(int j=0;j<fields;j++)
		{
			cout<<row[j]<<"  ";
		}
		cout<<"<br/>"<<endl;
	}
	return true;
}
