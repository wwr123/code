#include "contact.h"
enum op
{
	EXIT,    //��0��ʼ
	ADD,
	DEL,
	SEARCH,
	MOD,
	SHOW,
	SORT
};   //���Ӵ���Ŀɶ���
void menu()
{
	printf("****1.add 2.del 3.search 4.mod 5.show 6.sort 0.exit****\n");
}
int main()
{
	Con my_con;
	int input=1;
	Initcon(&my_con);
	while(input)
	{
		menu();
		printf("������:>");
		scanf("%d",&input);
		switch(input)
		{
		case ADD:
			{
			    add(&my_con);
			    break;
			}
		case DEL:
			{
			    del(&my_con);
			    break;
			}
		case SEARCH:
			{
			    search(&my_con);
			    break;
			}
		case MOD:
			{
			    mod(&my_con);
			    break;
			}
		case SHOW:
			{
			    show(&my_con);
			    break;
			}
		case SORT:
			{
				sort(&my_con);
				break;
			}
		case EXIT:
			{
				
				Savecontact(&my_con);
			    destory(&my_con);
			    Exit(&my_con);
			    break;
			}
		default:
			break;
		}
	}
	system("pause");
	return 0;

}