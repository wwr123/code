#include<iostream>
using namespace std;
#include<time.h>
#include<netinet/in.h>

//绑定sock和定时器
struct client_data
{
	sockaddr_in addr;
	int sockfd;
	heap_timer* timer;
};

//定时器类 
class heap_timer
{
	public:
		heap_timer(int time)
		{
			expire=time(NULL)+time;  //time函数返回当前时间
		}
	public:
		time_t expire; //定时器生效的绝对时间
		void (*cb_func) (client_data*);//回调函数
		client_data* user_data; //用户的数据
};

//时间堆--》堆中每个元素为定时器类的指针
class time_heap
{
	public:
		time_heap(int capa)
			:capacity(capa)
			,size(0)
	{
		array=new time_heap* [capacity]; //开辟数组 
		//初始化
		for(int i=0;i<capacity;i++)
		{
			array[i]=NULL;
		}
	}
		～time_heap()
		{
			for(int i=0;i<size;i++)
			{
				delete array[i];
			}
			delete [] array;
		}

		//添加定时器  时间复杂度o(logn)
		void add_timer(heap_timer* timer)
		{
			if(!timer)
				return;
			if(size>=capacity) //容量不够
			{
				//扩容-->扩大到原来的一倍
				recapacity();
			}
			array[sise]=timer; //将新加入的定时器放到数组的最后一个位置
			size++; //数组中的元素个数加1
			//向上调整
			adjustup(size-1);
		}

		//删除定时器  时间复杂度o(1) 
		void delete_timer(heap_timer* timer)
		{
			if(!timer)
				return;
			//将目标定时器的回调函数置为NULL，即延迟销毁
			//节省了时间，但容易造成数组膨胀
			timer->cb_func=NULL;  
		}
		//获得堆顶
		heap_timer* top()
		{
			if(empty())
				return NULL;
			return array[0];
		}
		//删除堆顶
		void pop()
		{
			if(empty())
				return;
			if(array[0])
			{
				delete array[0];
				array[0]=array[--szie];
				adjustdown(0); 
			}
		}
		bool empty()
		{
			return size==0;
		}
		//心搏函数   执行一个定时器的时间复杂度为o(1)
		void tick()
		{
			heap_timer* tmp=array[0];
			time_t cur=time(NULL); //循环处理堆中到期的定时器
			while(!empty())
			{
				if(!tmp)
					break;
				if(tmp->expire>cur) //时间没到期
				{
					break;
				}
				if(array[0]->cb_func) //到期
				{
					array[0]->cb_func(array[0]->user_data);
				}
				//
				pop();
				tmp=array[0];
			}
		}
	private:
		void adjustdown(int parent)
		{
			int child=parent*2+1;
			while(child<size)
			{
				if((child+1)<size&&(array[child]->expire)>(array[child+1]->expire))
					child++;
				if((array[child]->expire)<(array[parent]->expire))
				{
					swap(array[child],array[parent]);
					parent=child;
					child=parent*2+1;
				}
				else
					break;
			}
		}
		void adjustup(int child)
		{
			int parent=(child-1)/2;
			while(parent>=0)
			{
				if((array[child]->expire)<(array[parent]->expire))
				{
					swap(array[child],array[parent]);
					child=parent;
					pareniiighhh    lllll斤斤计较将接近接近    t=(child-1)/2;
				}
				else
					break;
			}
		}
		void recapacity()
		{
			time_heap** tmp=new time_heap* [capacity*2];
			if(!tmp)
			{
				return;
			}
			for(int i=0;i<capacity*2;i++)
			{
				tmp[i]=NULL;
			}
			for(int i=0;i<size;i++)
			{
				tmp[i]=array[i];
			}
			capacity=capacity*2;
			delete [] array;
			array=tmp;	
		}
	private:
		time_heap** array; //堆数组
		int capacity; //数组的容量
		int size;    //数组中元素的个数
};
