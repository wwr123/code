#include "commentconvert.h"
void DONULSTATE(FILE* pfin,FILE* pfout,enum STATE* state)
{
	int frist=0;
	int second=0;
	frist=fgetc(pfin);
	switch(frist)
	{
	case '/':
		{
			second=fgetc(pfin);
			switch(second)
			{
			case '*':
				{
					
					fputc('/',pfout);
					fputc('/',pfout);
					*state=C_STATE;
				}
				break;
			case '/':
				fputc(frist,pfout);
				fputc(second,pfout);
				*state=CPP_STATE;
				break;
			default:
				break;
			}
		}
		break;
	case EOF:
		*state=END_STATE;
		break;
	default:
		fputc(frist,pfout);
		break;
	}
}
void DOCSTATE(FILE* pfin,FILE* pfout,enum STATE* state)
{
	int frist=0;
	int second=0;
	int thrid=0;
	frist=fgetc(pfin);
	switch(frist)
	{
	case '*':
		{
			second=fgetc(pfin);
			switch(second)
			{
			case '/':
				thrid=fgetc(pfin);
				switch(thrid)
				{
				case '\n':
					fputc(thrid,pfout);
					*state=NUL_STATE;
					break;
				case '/':
					fputc('\n',pfout);
					ungetc(thrid,pfin);
					*state=NUL_STATE;
					break;
				default:
					fputc('\n',pfout);
					ungetc(thrid,pfin);  //³·Ïú×Ö·û
					*state=NUL_STATE;
					break;
				}
				break;
			default:
				fputc(frist,pfout);
				ungetc(second,pfin);

				break;
			}
		}
		break;
	case '\n':
		fputc(frist,pfout);
		fputc('/',pfout);
		fputc('/',pfout);
		break;
	default:
		fputc(frist,pfout);
		break;
	}
}
void DOCPPSTATE(FILE* pfin,FILE* pfout,enum STATE* state)
{
	int frist=0;
	frist=fgetc(pfin);
	switch(frist)
	{
	case '\n':
		fputc(frist,pfout);
		*state=NUL_STATE;
		break;
	case EOF:
		*state=END_STATE;
		break;
	default:
		fputc(frist,pfout);
		break;
	}
}
