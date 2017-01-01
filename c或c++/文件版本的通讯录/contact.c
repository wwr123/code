#include "contact.h"
void Initcon(pCon pcon)      //初始化
{
	pcon->con =(Peo*)malloc(DEFAULT*sizeof(Peo));
	if(pcon->con ==NULL)
	{
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	memset(pcon->con,0,DEFAULT*sizeof(Peo));  //
	pcon->count =0;
	pcon->capacity =DEFAULT;
	Loadcontact(pcon);
}
void check_capa(pCon pcon)    //检测
{
	Peo *ptr=NULL;
	if(pcon->count ==pcon->capacity )
	{
		 ptr=(Peo*)realloc(pcon->con ,(pcon->count +INC_COUNT)*sizeof(Peo));
		   if(ptr ==NULL)
	     {
		    printf("out of memory\n");
		    exit(EXIT_FAILURE);
	     }
	       else
	    {
		   pcon->con =ptr;
		   pcon->capacity =pcon->capacity  +INC_COUNT;
	    }
	}
	
}
void add(pCon pcon)        
{
	    check_capa(pcon);
		printf("name:");
		scanf("%s",pcon->con [pcon->count ].name);
		printf("age:");
        scanf("%d",&(pcon->con [pcon->count ].age));
		printf("sex:");
        scanf("%s",pcon->con [pcon->count ].sex);
		printf("tele:");
        scanf("%s",pcon->con [pcon->count ].tele);
		printf("addr:");
        scanf("%s",pcon->con [pcon->count ].addr );
		pcon->count++;
		
	
}
int find(pCon pcon)
{
    char name[10]={0};
	int i=0;
	printf("请输入姓名:>");
	scanf("%s",name);
	for(i=0;i<pcon->count ;i++)
	{
        if(strcmp(name,pcon->con [i].name)==0)
		{
			return i;
		}
	}
	return -1;
}
void del(pCon pcon)
{
	int i=0;
	int ret=0;
	if(pcon->count ==0)
	{
		printf("通讯录为空\n");
		return;
	}
	ret=find(pcon);
	if(ret==-1)
	{
		printf("没有找到\n");
	}
	else
	{
		for(i=ret;i<pcon->count-1;i++)
		{
			pcon->con [i]=pcon->con [i+1];
		}
        pcon->count --;
		printf("删除成功\n");
	}
	
}
void search(pCon pcon)
{
	int ret=0;
	if(pcon->count ==0)
	{
		printf("通讯录为空\n");
		return;
	}
	ret=find(pcon);
	if(ret==-1)
	{
		printf("没有找到\n");
	}
	else
	{
	
		printf("%5s\t%s\t%5s\t%5s\t%5s\n","name","age","sex","tele","addr");
		printf("%5s\t%d\t%5s\t%5s\t%5s\n",pcon->con [ret ].name,
			pcon->con [ret ].age,pcon->con [ret].sex,
			pcon->con [ret ].tele,pcon->con [ret ].addr);
	}
}
void mod(pCon pcon)
{
	int ret=0;
	if(pcon->count ==0)
	{
		printf("通讯录为空\n");
		return;
	}
    ret=find(pcon);
	if(ret==-1)
	{
		printf("没有找到\n");
	}
	else
	{
		printf("name:");
		scanf("%s",&(pcon->con [ret].name) );
		printf("age:");
        scanf("%d",&(pcon->con [ret ].age));
		printf("sex:");
        scanf("%s",&(pcon->con [ret].sex) );
		printf("tele:");
        scanf("%s",&(pcon->con [ret].tele) );
		printf("addr:");
        scanf("%s",&(pcon->con [ret].addr) );
	}
}
void sort(pCon pcon)     //从小到大
{
	int flag=0;
	int i=0;
	int j=0;
	for(i=0;i<pcon->count -1;i++)
	{
		flag=1;
		for(j=0;j<pcon->count -i-1;j++)
		{
			if(strcmp(pcon->con [j].name ,pcon->con [j+1].name )>0)
			{
				Peo tmp=pcon->con [j];
				pcon->con [j]=pcon->con [j+1];
				pcon->con [j+1]=tmp;
				flag=0;
			}

		}
		if(flag==1)
			break;
	}
 //show(pcon);
	printf("排序完成\n");
}
void Exit(pCon pcon)
{
	exit(0);
}


void show(pCon pcon)
{
	int i=0;
	printf("%5s\t%s\t%5s\t%5s\t%5s\n","name","age","sex","tele","addr");
	//printf("%d\n",pcon->count );
	for(i=0;i<pcon->count ;i++)
	{
		printf("%5s\t%d\t%5s\t%5s\t%5s\n",pcon->con [i ].name,
			pcon->con [i ].age,pcon->con [i ].sex,
			pcon->con [i ].tele,pcon->con [i].addr);
	}
}

void destory(pCon pcon)
{
	if(pcon->con !=NULL)
	{
		free(pcon->con );
		pcon->con =NULL;
	}
}


void Loadcontact(pCon pcon)    //加载
{
	Peo tmp={0};
	FILE *pfread=fopen(FILENAME,"r");
	if(pfread==NULL)
	{
		perror(FILENAME);
		exit(EXIT_FAILURE);
	}
	while(fread(&tmp,sizeof(Peo),1,pfread))    //读取
	{
		 check_capa(pcon);
		 pcon->con [pcon->count ++]=tmp;    //赋值
	}
	fclose(pfread);                     
}
void Savecontact(pCon pcon)
{
	FILE *pfwrite=fopen(FILENAME,"w");
	int i=0;
	if(pfwrite==NULL)
	{
		perror(FILENAME);
		exit(EXIT_FAILURE);
	}
	for(i=0;i<pcon->count ;i++)
	{
		fwrite(pcon->con +i,sizeof(Peo),1,pfwrite);
	}
	fclose(pfwrite);
}
