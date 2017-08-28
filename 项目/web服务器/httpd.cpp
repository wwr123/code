#include"httpd.h"

void httpd::process()
{
	 accept_handler();
    printf("procsessssssss\n");
}
void httpd::init(int fd)
{
	sock=fd;
	m_linger=false;
}
void echo_404(int sock)
{
	char line[SIZE];
	sprintf(line,"HTTP/1.1 404 Not Found \r\n");
	send(sock,line,strlen(line),0);
	send(sock,"\r\n",strlen("\r\n"),0);
	sprintf(line,"404 NOT Found \r\n");
	send(sock,line,strlen(line),0);
}
void echo_errno(int error_code,int sock)
{
	switch(error_code)
	{
		case 404:
			echo_404(sock);
	}
}
static int get_line(int sock,char *buf)
{	
	char c;
	ssize_t s=0;
	int i=0;
	while(s=recv(sock, &c,1,0) > 0)
	{
		if(c=='\r')
		{
			if((s=recv(sock, &c, 1, MSG_PEEK)>0)&&c=='\n')
			{
				s=recv(sock, &c, 1, 0);
			}
			buf[i++]='\n';
			break;
		}
		else if(c=='\n')
		{
			buf[i++]=c;
			break;
		}
		else
		{
			buf[i++]=c;
		}
	}
	buf[i] = 0;
	return i;//返回读到的个数
}
void clear_head(int sock)
{
	int ret=0;
	char line[SIZE];
	do
	{
		 ret = get_line(sock, line);
	}while(ret>0 && ret != 1 && strcmp(line,"\n")!=0);
}

static int  echo_www(int sock,char* Path,ssize_t size,bool& m_linger)
{
	printf("not cgi\n");
	int fd=open(Path,O_RDONLY);
	if(fd<0)
	{
		echo_errno(404,sock);  //差错处理404
		return 8;
	}
    printf("errno\n");
	//判断请求报头中的长连接状态
	char buf[SIZE];
	int ret=0;
	do
	{
		//printf("hhhhhhh\n");
		ret=get_line(sock,buf);
		printf("buf:%s\n",buf);
		if(ret!=-1&&strncmp(buf,"Connection: ",12)==0)
		{
			printf("strncmp con\n");
			printf("buf+12:%s\n",buf+12);
			if(strncmp(buf+12,"keep-alive",10)==0)
			{
	            printf("strcmp keep\n");
				m_linger=true;
				printf("m_linger:%d\n",m_linger);
			}
			
		}
	}while(ret!=-1&&strcmp(buf,"\n")!=0); //一直读到空行才结束
   printf("keep alive end\n");

	//回写响应
	char line[SIZE];
	sprintf(line,"HTTP/1.1 200 OK\r\n");
	send(sock,line,strlen(line),0);
	char* content_type="Content-Type: text/html;charset=ISO-8859-1\r\n";
	send(sock,content_type,strlen(content_type),0);
	if(m_linger==true)
	{
		content_type="Connection: keep-alive\r\n";
		printf("keep\n");
	}
	else
	{
		content_type="Connection: close\r\n";
		printf("not keep\n");
	}
	send(sock,content_type,strlen(content_type),0);
	send(sock,"\r\n",strlen("\r\n"),0);

	printf("http end\n");

	if(sendfile(sock,fd,0,size)<0)  //把fd中的内容写到sock中
	{
		echo_errno(404,sock);
		close(fd);
		return 9;
	}
    
//	close(fd);
	printf("ssend file\n");
}


int excu_cgi(int sock,char* method,char* Path,const char* querry,bool& m_linger)
{
	//为了配置环境变量
	char method_env[SIZE/8];
	char querry_env[SIZE/4];
	char content_len_env[SIZE/8];
	int content_len=-1;
    m_linger=false;
	if(strcasecmp(method,"GET")==0)
	{
		//clear_head(sock);
		char buf[SIZE];
		int ret=0;
		do
		{
			//printf("hhhhhhh\n");
			ret=get_line(sock,buf);
			printf("buf:%s\n",buf);
			if(ret!=-1&&strncmp(buf,"Connection: ",12)==0)
			{
				printf("strncmp\n");
				if(strncmp(buf+12,"keep-alive",10)==0)
				{
					m_linger=true;
					printf("m_linger:%d",m_linger);
				}
				
			}
		}while(ret!=-1&&strcmp(buf,"\n")!=0); //一直读到空行才结束
	}
	else
	{
		//post方法
		char buf[SIZE];
		int ret=0;
		do
		{
			ret=get_line(sock,buf);
			if(ret!=-1&&strncmp(buf,"Content-Length: ",16)==0)
			{
	  		 	//conten t-legth  请求内容长度
 				content_len=atoi(buf+ 16);
			}
			else if(ret!=-1&&strncmp(buf,"Connection: ",12)==0)
			{
				if(strncmp(buf+12,"keep-alive",10)==0)
					m_linger=true;
			}
		}while(ret!=-1&&strcmp(buf,"\n")!=0); //一直读到空行才结束

		if(content_len<0)
		{
			//echo_errno();
			return 10;
		}
	}	
		//回写响应行
		char line[SIZE];
		sprintf(line,"HTTP/1.1 200 OK\r\n");
		send(sock,line,strlen(line),0);
	    char* content_type="Content-Type: text/html;charset=ISO-8859-1\r\n";
		send(sock,content_type,strlen(content_type),0);
		if(m_linger==true)
			content_type="Connection: keep-alive\r\n";
		else
			 content_type="Connection: close\r\n";
		send(sock,content_type,strlen(content_type),0);
		send(sock,"\r\n",strlen("\r\n"),0);

		printf("htpp construct end\n");
	
		//创建2个管道，让父子进程进行通信
		int input[2];  //站在子进程的角度命名
		int output[2];
		pipe(input);
		pipe(output);

		pid_t id=fork();
		if(id==0)
		{
			close(input[1]);
			close(output[0]);
			close(sock);
			//child
			//1.重定向文件描述符
			dup2(input[0],0); //标准输入指向input[0]
			dup2(output[1],1);//让标准输出指向output[1];
			
			//2.为了让子进程exec，需要将参数配置成环境变量。
			sprintf(method_env,"METHOD=%s",method);
			putenv(method_env);  //增加环境变量
			sprintf(querry_env,"QUERRY=%s",querry);
			putenv(querry_env);
			sprintf(content_len_env,"CONTENT_LEN=%d",content_len);
			putenv(content_len_env);
		
			//3.进行程序替换exec()
			execl(Path, Path, NULL);
			exit(1);
		}
		else
		{
			close(input[0]);
			close(output[1]);
			//father
			//如果方法为post,继续从sock中读取参数，写到管道中
			//子进程的exec需要用
			if(strcasecmp(method,"POST")==0)
			{
	
				char c='\0';
				int i=0;
				for( ; i<content_len; ++i)
				{
			 		recv(sock,&c,1,0);
				    write(input[1], &c, 1);
				} 
			}
			//读子进程在管道的返回值，写到sock中
			char ch = 0;
			while(read(output[0], &ch, 1) > 0)
			{
		 		send(sock, &ch, 1, 0); 
				//printf("ch:%c ",ch);
			}
			//非阻塞等待,拿到子进程的退出码
			waitpid(id,NULL,0);
		}
}

int httpd::accept_handler()
{
	printf("accept handler\n");
	char buf[SIZE];
	char method[SIZE];
	char path[SIZE]; 
	char* querry = NULL;
	int i=0;
	int cgi=0;
	int j=0;
	int end=0;
	char Path[SIZE];
	int ret=0; 

	int ret1 = get_line(sock, buf);  //ret1为读到一行的字节数
	while(!isspace(buf[i]))
	{
		method[i]=buf[i];
		i++;
	}
	method[i]='\0';
 	if(strcasecmp(method,"POST")==0) //cgi必定为1
	{
		cgi=1;
	}
		i++;   //i所在的位置为空格
		//path aa/bb?data1=100&data2=200
		while(buf[i]!=' ')
		{
			path[j++]=buf[i++];
		}
		path[j]='\0';
	if(strcasecmp(method,"GET")==0) 
	{
		querry=path;
		while(*querry)
		{
		if(*querry=='?')
		{
			*querry='\0';
			cgi=1;
			querry++;
			break;
		}
		else
			querry++;
		}
	}
	//Path wwwroot/aa/bb
	sprintf(Path,"wwwroot%s",path); //添加根目录
	if(Path[strlen(Path)-1]=='/')  //是文件夹
	{
		strcat(Path,"index.html"); 
	}

	struct stat st;
    if(stat(Path,&st)<0) //判断文件是否存在，失败-1，成功0
    {
		echo_errno(404,sock);
		ret=7;
	    close(sock);
		//goto end;
    }
	if(S_ISDIR(st.st_mode))//是目录文件 S_ISDIR是一个宏
	{
		strcat(Path,"/index.html");
	}
	else if((S_IXUSR&st.st_mode)||(S_IXGRP&st.st_mode)||(S_IXOTH&st.st_mode)) //可执行文件 
	{
		cgi=1;
	}
	if(cgi)  //cgi模式
	{
		ret=excu_cgi(sock,method,Path,querry,m_linger);
		printf("cgi end\n");
	}
	else
	{
		//不是cgi模式
		//清除头部信息
		//clear_head(sock);
		ret=echo_www(sock,Path,st.st_size,m_linger);
		printf("not cgi end\n");
	}
    
	if(m_linger==false)  //false
	{
		close(sock);  //把sock从epfd中删除
		printf("false\n");
	}
	printf("true\n");

	return ret;
}
