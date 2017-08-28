#ifndef _HTTPD_H_
#define _HTTPD_H_
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/sendfile.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/epoll.h>
#define SIZE 10240

class httpd
{
	public:
		void process();    //工作线程的入口函数
		void init(int fd); //初始化sock
        bool m_linger;     //判断是否为长连接
	private:
		int accept_handler(); 
		int sock;
};
#endif
