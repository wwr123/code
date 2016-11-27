#include "commentconvert.h"

int main()
{
	int frist=0;
	FILE* pfout=NULL;
	FILE* pfin=NULL;
    enum STATE state=NUL_STATE;
    pfin=fopen(INPUT,"r");
	if(pfin==NULL)
	{
		perror("out of read");
		exit(EXIT_FAILURE);
	}
    pfout=fopen(OUTPUT,"w");
	if(pfout==NULL)
	{
		perror("out of write");
		fclose(pfin);
		exit(EXIT_FAILURE);
	}
	while(state!=END_STATE)
	{
		switch(state)
		{
		case NUL_STATE:
			{
				DONULSTATE(pfin,pfout,&state);
			}
			break;
		case C_STATE:
			{
				DOCSTATE(pfin,pfout,&state);
			}
			break;
		case CPP_STATE:
			{
				DOCPPSTATE(pfin,pfout,&state);
			}
			break;
		default:
			break;
		}
	}
	printf("×ª»»³É¹¦\n");
	system("pause");
	return 0;
}