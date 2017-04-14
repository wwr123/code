#ifndef _HTTPD_H_
#define _HTTPD_H_
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define SIZE 10240
enum error_code
{
	FATAL=0,
	NORMAL=1,
	WARNING=2
};
void print_log(char* str1,enum error_code code);
void* accept_handler(void* arg);
#endif
