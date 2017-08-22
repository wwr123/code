#include<iostream>
using namespace std;
#include<list>
#include<pthread.h>
#include<semaphore.h>
#include<errno.h>
#include<cstdio>

class mutexlock
{
	public:
		mutexlock()
		{
			pthread_mutex_init(&mutex,NULL);
		}
		void lock()
		{
			pthread_mutex_lock(&mutex);
		}
		void unlock()
		{
			pthread_mutex_unlock(&mutex);
		}
		~mutexlock()
		{
			pthread_mutex_destroy(&mutex);
		}
	private:
		pthread_mutex_t mutex;
};

class Sem
{
	public:
	    Sem()
		{
			sem_init(&s,0,0);
		}
		void wait()
		{
			sem_wait(&s); //p
		}
		void post()
		{
			sem_post(&s);//v
		}
		~Sem()
		{
			sem_destroy(&s);
		}
	private:
		sem_t s;
};

template<class T> //T是任务类，模板增加了代码的复用性
class threadpool
{
	public:
		threadpool(int num1,int num2);
		bool appendrequest(T* request);
		~threadpool();
	private:
        static void* start_routine(void* arg);
		void run();
		int threadnums; //线程的数目
		int requestlist; //请求队列的大小
		pthread_t* threadbuf; //用来r存放线程id
		list<T*> l;  //请求队列,底层为双向链表
		mutexlock ml; //保护请求队列的互斥锁
	    Sem sem; //信号量，是否有任务需要处理
		bool flag; //判断主进程有没有退出
};
