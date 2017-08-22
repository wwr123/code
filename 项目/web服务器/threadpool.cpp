#include"threadpool.h"

template<class T> //T是任务类，模板增加了代码的复用性
threadpool<T>::threadpool(int num1=10,int num2=1000)
			:threadnums(num1)
			,requestlist(num2)
			,flag(false)
    	{
			threadbuf=new pthread_t[threadnums]; 
			//开辟threadnums大小的数组，存放线程id
			
			//创建线程
			for(int i=0;i<threadnums;i++)
			{
				cout<<"pthread start"<<endl;
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

template<class T> //T是任务类，模板增加了代码的复用性
bool threadpool<T>::appendrequest(T* request) //把请求任务添加到队列中
		{
			cout<<"appendrequest start"<<endl;
			ml.lock(); //因为他被所有的线程共享，加锁，只允许一个线程执行
			if(l.size()>=requestlist)
			{
				ml.unlock();
				return false;
			}
			l.push_back(request);
            ml.unlock();
			sem.post();
			return true;
		}

template<class T> //T是任务类，模板增加了代码的复用性
threadpool<T>::~threadpool()
		{
			cout<<"~threadpool"<<endl;
			delete []threadbuf;
			flag=true;
		}

template<class T> //T是任务类，模板增加了代码的复用性
void threadpool<T>::run()
		{
			//所有的线程执行到这一步了
			while(!flag) //一个线程执行完后，他会继续排队再次执行，而不是直接销毁了
			{
				sem.wait();
				ml.lock(); //只有一个线程获得了锁
				while(l.empty())
				{
					ml.unlock();
					continue;
				}
				T* front=l.front(); //得到请求任务
				cout<<"run start"<<endl;
				l.pop_front();
				ml.unlock();
				if(!front)
					continue;
				front->process(); //线程就去执行这个请求任务
			}	
		}

template<class T>
void* threadpool<T>::start_routine(void* arg)   //线程开始运行的函数
{
	threadpool* p=(threadpool*)arg;  //必须要传的
	p->run();
	return p;
}
