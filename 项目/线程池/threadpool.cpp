#include<iostream>
using namespace std;
#include<queue>
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
			sem_wait(&s);
		}
		void post()
		{
			sem_post(&s);
		}
		~Sem()
		{
			sem_destroy(&s);
		}
	private:
		sem_t s;
};

template<class T>
class threadpool
{
	public:
		threadpool(int num1=10,int num2=1000)
			:threadnums(num1)
			,requestqueue(num2)
			,flag(false)
    	{
			threadbuf=new pthread_t[threadnums]; 
			//开辟threadnums大小的数组，存放线程id
			
			//创建线程
			for(int i=0;i<threadnums;i++)
			{
				if(pthread_create(threadbuf+i,NULL,start_routine,(void*)this))
					//pthread_create要调用类的从成员函数，必须把函数声明为静态的
				{
					delete []threadbuf;
					perror("pthread_create");
				}
				if(pthread_detach(threadbuf[i])) //分离线程
				{
					delete []threadbuf;
					perror("pthread_detach");
				}
			}
		}
		bool workrequest(T* request) //把请求放到队列中
		{
			ml.lock(); //加锁，只允许一个线程执行
			q.push(request);
            ml.unlock();
			//sem.post();
		}
		~threadpool()
		{
			delete []threadbuf;
			flag=true;
		}

	private:
        static void* start_routine(void* arg);   //线程开始运行的函数
		void run()
		{
			//所有的线程执行到这一步了
			while(!flag) //一个线程执行完后，他会继续排队再次执行，而不是直接销毁了
			{
				//sem.wait();
				ml.lock(); //只有一个线程获得了锁
				while(q.empty())
				{
					ml.unlock();
					continue;
				}
				T* front=q.front(); //得到请求任务
				q.pop();
				ml.unlock();
				//front->protmethod(); //线程就去执行这个请求任务
			}	
		}
		int threadnums; //线程的数目
		int requestqueue; //请求队列的大小
		pthread_t* threadbuf; //用来r存放线程id
		queue<T*> q;  //请求队列
		mutexlock ml; //互斥锁
	    Sem sem; //信号量
		bool flag; //判断主进程有没有退出
};	
template<class T>
void* threadpool<T>::start_routine(void* arg)   //线程开始运行的函数
{
	threadpool* p=(threadpool*)arg;  //必须要传的
	p->run();
	return p;
}
int main()
{
	threadpool<int> pool;
	return 0;
}
