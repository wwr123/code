#include<mysql.h>
#include<iostream>
using namespace std;

class MysqlOp
{
	public:
		MysqlOp()
		{}
		~MysqlOp()
		{
			mysql_close(conn);
		}
	public:
		bool SetConnect(const char* host,const char* user,const char* passwd,const char* mysql_name);
		bool Insert(const char* info);
		bool Delete(const char* info);
		bool Select(const char* info);
		bool Update(const char* info);
	private:
		MYSQL* conn;
};
