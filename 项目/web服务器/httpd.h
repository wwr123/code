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
#define SIZE 10240
#include<ctype.h>
#include<sys/epoll.h>
class httpd
{
	public:
		void process();
		void init(int fd);
	private:
		int accept_handler();
        
		int sock;
};
#endif
