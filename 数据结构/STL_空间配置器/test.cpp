#include<iostream>
using namespace std;

typedef void(*MALLOCALLOC) ();
//һ���ռ�������
template <int inst>
class __Malloc_Alloc_Template 
{
private:
	static void *Oom_Malloc(size_t); //�ڴ治�㴦����
	static MALLOCALLOC _Malloc_Alloc_Oom_Handler; //����ָ�룬�ڴ治���ʱ��Ĵ������
public:
	static void* Allocate(size_t n) //n>128,��mallocֱ�ӿ���
	{
		void *result = malloc(n);
		if (0 == result)   //����ʧ��
			result = Oom_Malloc(n);//�����ڴ治�㴦����
		return result;
	}
		
	static void Deallocate(void *p)  //�ͷ��ڴ�
	{
		free(p);
	}

	static void (* Set_Malloc_Handler(MALLOCALLOC f) //���û��������ڴ治��ʱ�Ĵ������
	{
		MALLOCALLOC old = _Malloc_Alloc_Oom_Handler;
		_Malloc_Alloc_Oom_Handler = f;
		return old;
	}
};

template <int inst>       
void (*__Malloc_Alloc_Template<inst>::_Malloc_Alloc_Oom_Handler)()=0 ;//�������ڴ治��Ĵ������

template <int inst>
void* __Malloc_Alloc_Template<inst>::Oom_Malloc(size_t n)
{
	MALLOCALLOC My_Malloc_Handler; //���庯��ָ��
	void* result;
	while(1)
	{
		My_Malloc_Handlerr=_Malloc_Alloc_Oom_Handler;
		if(My_Malloc_Handlerr==0) //�����ô�����ƣ�ֱ���׳��쳣
		{
			throw bad_alloc();
		}
		(*My_Malloc_Handlerr)();  //�����ڴ治�㴦����Ƶĺ����������ͷ������ط����ڴ� 
		result=malloc(n);
		if(result)
		{
			return result;
			break;
		}
	}
}

//�����ռ�������
template <bool threads, int inst>
class __Default_Alloc_Template 
{
private:
	enum {__ALIGN = 8}; //��׼
    enum {__MAX_BYTES = 128};  //�����ֽڸ���
    enum {__NFREELISTS = __MAX_BYTES/__ALIGN}; //��������ĳ���
	union obj   //��������Ľڵ�����
	{
        union obj * free_list_link;
        char client_data[1];    /* The client sees this.        */
    };
	static size_t ROUND_UP(size_t bytes) //��bytesȡ����ȡ��8��������
	{
        return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
    }
	
	static  size_t FREELIST_INDEX(size_t bytes) 
	    //��������bytes��С�Ŀ�������������Ǹ�λ���Ϲ���
	{
        return (((bytes) + __ALIGN-1)/__ALIGN - 1);
	}
	static obj * volatile free_list[__NFREELISTS]; //����һ����������
	static char *start_free; //�ڴ�ص�ͷָ��
    static char *end_free;   //�ڴ�ص�βָ��
    static size_t heap_size; //��¼�ڴ���Ѿ���ϵͳ�����˶����ڴ�
  
public:
  static void * Allocate(size_t n) //n<128������ռ�
  {
		obj * volatile * my_free_list;  //��ֹ�������Ż�����ֹʹ��һ���߳̿����޸�
		void* result;

		if (n > (size_t) __MAX_BYTES)     //n>128,ֱ�ӵ���һ���ռ�������
		{
			return Malloc_Alloc::Allocate(n);
		}

		//��������������
		my_free_list = free_list + FREELIST_INDEX(n); //ָ��������������Ǹ�λ����
		result = *my_free_list; //resultָ������ڵ�����ҵĿռ�
		if (result == 0) //����ڵ���û���ڴ�
		{
			void *r = refill(ROUND_UP(n)); //ȥ�ڴ������
			return r;
		}
		//���ſ����ڴ棬ֱ�ӷ���
		*my_free_list = result -> free_list_link; //�ѵڶ���ռ��ַ�ҵ���������ڵ�����
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
		//ͷ�嵽����������
		my_free_list = free_list + FREELIST_INDEX(n);
		q -> free_list_link = *my_free_list;
		*my_free_list = q;
  }
private:
  static void* refill(size_t n)//ȥ�ڴ������
  {
	    int nobjs = 20; //���ڴ��һ��������20��
		char * chunk = chunk_alloc(n, nobjs); 
		obj * volatile * my_free_list;
		if (1 == nobjs) 
			return chunk;
		obj* result = (obj *)chunk;    //������ĵ�һ�����󷵻�
		 
		my_free_list = free_list + FREELIST_INDEX(n);
		//��ʣ��Ĺҵ�����������
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
    size_t total_bytes = size * nobjs;  //�ܹ�Ҫ������ֽ���
    size_t bytes_left = end_free - start_free; //�ڴ��ʣ����ֽ���

    if (bytes_left >= total_bytes)  //���� 
	{
        result = start_free;
        start_free += total_bytes;
        return result;
    } 
	else if (bytes_left >= size)   //������һ����������
	{
        nobjs = bytes_left/size;  
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    } 
	else //һ����������
	{
        size_t New = 2 * total_bytes + ROUND_UP(heap_size >> 4); //�ڴ�ؿ����µ�����
        if (bytes_left > 0) //ʣ����ڴ�ҵ�����������
		{
            obj * volatile * my_free_list =free_list + FREELIST_INDEX(bytes_left);
            ((obj *)start_free) -> free_list_link = *my_free_list;  //ͷ��
            *my_free_list = (obj *)start_free;
        }

        start_free = (char *)malloc(New);
        if (0 == start_free) //û���ڴ棬��������������һ����n���ڴ�
		{
            obj * volatile * my_free_list, *p;
            for (int i = size; i <= __MAX_BYTES; i += __ALIGN) 
			{
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (0 != p) //�ҵ�һ���ڴ�
				{
                    *my_free_list = p -> free_list_link;
                    start_free = (char *)p;  //�����ռ仹���ڴ��
                    end_free = start_free + i;
                    return chunk_alloc(size, nobjs);
                }
            }
			//Ҫ�����Ҳ����Ļ����͵�һ���ռ����������������ڴ治�㴦�����,
			//Ҫ�ǻ����еĻ��������Զ��׳��쳣
	        end_free = 0;	
            start_free = (char *)__Malloc_Alloc_Template<0>::Allocate(New); 
        }
        heap_size += New;
        end_free = start_free + New;
        return chunk_alloc(size, nobjs); //�ڵ���һ���������ڴ�
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