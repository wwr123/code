#ifndef _COMMENTCONVERT_H__
#define _COMMENTCONVERT_H__
#include <stdio.h>
#include <stdlib.h>

#define INPUT "input.c"
#define OUTPUT "output.c"

enum STATE
{
	END_STATE,
	NUL_STATE,
	C_STATE,
	CPP_STATE
	
};
void DONULSTATE(FILE* pfin,FILE* pfout,enum STATE* state);
void DOCSTATE(FILE* pfin,FILE* pfout,enum STATE* state);
void DOCPPSTATE(FILE* pfin,FILE* pfout,enum STATE* state);


#endif //_COMMENTCONVERT_H__