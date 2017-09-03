#include"httpd.h"
#include"threadpool.cpp"

//创建线程池
threadpool<httpd> t(10,1000);
httpd arr[1000];
for(int i=0;i<1000;i++)
{
	arr[i].init(i);
}

int startup(char* ip,int port)
{
	int listen_sock=socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock<0)
	{
		exit(2);
	}
	int opt=1;
    setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=inet_addr(ip);
	local.sin_family=AF_INET;
	socklen_t len=sizeof(local);
	if(bind(listen_sock,(struct sockaddr*)&local,len) < 0)
	{
		exit(3);
	}
	if(listen(listen_sock,5)<0)
	{
		exit(4);
	}
	return listen_sock;
}

void accept_cb(int fd,short event,void* arg)
{
	t.appendrequest(&arr[sockfd]);//把任务添加到队列中
}
void sock_cb(int fd,short event,void* arg)
{
	int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
	if(sock<0)
	{
		continue;
	}

	struct event* ev_accept;
	event_set(ev_accept,,EV_READ|EV_ET,accept_cb,NULL);
	event_add(ev_accept,NULL);

}
void timer_cb(int fd,short event,void* arg)
{
	printf("timeout\n");
}

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		exit(1);
	}
	int listen_sock=startup(argv[1],atoi(argv[2]));
    
    
    
	//创建一个Reactor实例
	struct event_base* base=event_base_new();
	struct event* ev_sock;
	event_set(ev_sock,listen_sock,EV_READ|EV_ET,sock_cb,NULL); //创建事件
    event_add(ev_sock,NULL);

    

	//创建定时事件
	struct event* ev_timer;
	event_set(ev_timer,-1,0,timer_cb,NULL);
	timeval tv={5,0};  //相当于一个定时器
	event_add(ev_timer,&tv);

	//执行循环
	event_base_dispatch(base);

    
	return 0;
}
