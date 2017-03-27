#include<iostream>
using namespace std;

typedef void(*MALLOCALLOC) ();
//一级空间配置器
template <int inst>
class __Malloc_Alloc_Template 
{
private:
	static void *Oom_Malloc(size_t); //内存不足处理函数
	static MALLOCALLOC _Malloc_Alloc_Oom_Handler; //函数指针，内存不足的时候的处理机制
public:
	static void* Allocate(size_t n) //n>128,就malloc直接开辟
	{
		void *result = malloc(n);
		if (0 == result)   //开辟失败
			result = Oom_Malloc(n);//调用内存不足处理函数
		return result;
	}
		
	static void Deallocate(void *p)  //释放内存
	{
		free(p);
	}

	static void (* Set_Malloc_Handler(MALLOCALLOC f) //让用户来设置内存不足时的处理机制
	{
		MALLOCALLOC old = _Malloc_Alloc_Oom_Handler;
		_Malloc_Alloc_Oom_Handler = f;
		return old;
	}
};

template <int inst>       
void (*__Malloc_Alloc_Template<inst>::_Malloc_Alloc_Oom_Handler)()=0 ;//不设置内存不足的处理机制

template <int inst>
void* __Malloc_Alloc_Template<inst>::Oom_Malloc(size_t n)
{
	MALLOCALLOC My_Malloc_Handler; //定义函数指针
	void* result;
	while(1)
	{
		My_Malloc_Handlerr=_Malloc_Alloc_Oom_Handler;
		if(My_Malloc_Handlerr==0) //不设置处理机制，直接抛出异常
		{
			throw bad_alloc();
		}
		(*My_Malloc_Handlerr)();  //调用内存不足处理机制的函数，申请释放其他地方的内存 
		result=malloc(n);
		if(result)
		{
			return result;
			break;
		}
	}
}

//二级空间配置器
template <bool threads, int inst>
class __Default_Alloc_Template 
{
private:
	enum {__ALIGN = 8}; //基准
    enum {__MAX_BYTES = 128};  //最大的字节个数
    enum {__NFREELISTS = __MAX_BYTES/__ALIGN}; //自由链表的长度
	union obj   //自由链表的节点类型
	{
        union obj * free_list_link;
        char client_data[1];    /* The client sees this.        */
    };
	static size_t ROUND_UP(size_t bytes) //把bytes取向上取成8的整数倍
	{
        return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
    }
	
	static  size_t FREELIST_INDEX(size_t bytes) 
	    //用来计算bytes大小的空闲区在链表的那个位置上挂着
	{
        return (((bytes) + __ALIGN-1)/__ALIGN - 1);
	}
	static obj * volatile free_list[__NFREELISTS]; //定义一个自由链表
	static char *start_free; //内存池的头指针
    static char *end_free;   //内存池的尾指针
    static size_t heap_size; //记录内存池已经向系统申请了多大的内存
  
public:
  static void * Allocate(size_t n) //n<128，分配空间
  {
		obj * volatile * my_free_list;  //防止编译器优化，防止使另一个线程可以修改
		void* result;

		if (n > (size_t) __MAX_BYTES)     //n>128,直接调用一级空间配置器
		{
			return Malloc_Alloc::Allocate(n);
		}

		//在自由链表中找
		my_free_list = free_list + FREELIST_INDEX(n); //指向在自由链表的那个位置上
		result = *my_free_list; //result指向这个节点下面挂的空间
		if (result == 0) //这个节点下没有内存
		{
			void *r = refill(ROUND_UP(n)); //去内存池申请
			return r;
		}
		//挂着空闲内存，直接返回
		*my_free_list = result -> free_list_link; //把第二块空间地址挂到自由链表节点下面
		return result;
  }

  static void deallocate(void *p, size_t n)
	  {
		obj *q = (obj *)p;
		obj * volatile * my_free_list;

		if (n > (size_t) __MAX_BYTES) //n>128
		{
			__Malloc_Alloc_Template<0>::Deallocate(q);
			return;
		}
		//头插到自由链表中
		my_free_list = free_list + FREELIST_INDEX(n);
		q -> free_list_link = *my_free_list;
		*my_free_list = q;
  }
private:
  static void* refill(size_t n)//去内存池申请
  {
	    int nobjs = 20; //向内存池一次性申请20个
		char * chunk = chunk_alloc(n, nobjs); 
		obj * volatile * my_free_list;
		if (1 == nobjs) 
			return chunk;
		obj* result = (obj *)chunk;    //将申请的第一个对象返回
		 
		my_free_list = free_list + FREELIST_INDEX(n);
		//将剩余的挂到自由链表上
		*my_free_list = (obj *)(chunk + n); 
		obj* cur=*my_free_list;
		for (int i = 2;i<nobjs; i++) 
		{
			obj* next= (obj*)(chunk + n*i);  
            cur->_freeListLink = next;  
            cur = next; 
		} 
		cur->_freeListLink = 0;  
		
	    return result;
  }
  char* chunk_alloc(size_t size, int& nobjs)
  {
    char * result;
    size_t total_bytes = size * nobjs;  //总共要申请的字节数
    size_t bytes_left = end_free - start_free; //内存池剩余的字节数

    if (bytes_left >= total_bytes)  //满足 
	{
        result = start_free;
        start_free += total_bytes;
        return result;
    } 
	else if (bytes_left >= size)   //至少有一个对象满足
	{
        nobjs = bytes_left/size;  
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    } 
	else //一个都不满足
	{
        size_t New = 2 * total_bytes + ROUND_UP(heap_size >> 4); //内存池开辟新的容量
        if (bytes_left > 0) //剩余的内存挂到自由链表上
		{
            obj * volatile * my_free_list =free_list + FREELIST_INDEX(bytes_left);
            ((obj *)start_free) -> free_list_link = *my_free_list;  //头插
            *my_free_list = (obj *)start_free;
        }

        start_free = (char *)malloc(New);
        if (0 == start_free) //没有内存，在自由链表中找一个比n的内存
		{
            obj * volatile * my_free_list, *p;
            for (int i = size; i <= __MAX_BYTES; i += __ALIGN) 
			{
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (0 != p) //找到一块内存
				{
                    *my_free_list = p -> free_list_link;
                    start_free = (char *)p;  //将这块空间还给内存池
                    end_free = start_free + i;
                    return chunk_alloc(size, nobjs);
                }
            }
			//要是再找不到的话，就调一级空间配置器，其中有内存不足处理机制,
			//要是还不行的话，他会自动抛出异常
	        end_free = 0;	
            start_free = (char *)__Malloc_Alloc_Template<0>::Allocate(New); 
        }
        heap_size += New;
        end_free = start_free + New;
        return chunk_alloc(size, nobjs); //在调用一次来分配内存
    }
 

};

template <bool threads, int inst>
char *__Default_Alloc_Template<threads,inst>::start_free=0; 
template <bool threads, int inst>
char *__Default_Alloc_Template<threads,inst>::end_free=0;   
template <bool threads, int inst>
size_t __Default_Alloc_Template<threads,inst>::heap_size=0; 
template <bool threads, int inst>
class _DefaultAllocTemplate<threads, inst>::obj * volatile
_DefaultAllocTemplate<threads, inst>::free_list[__NFREELISTS]={0};