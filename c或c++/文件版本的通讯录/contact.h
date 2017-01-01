#ifndef __CONCATE_H__
#define __CONCATE_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 10
#define MAX_SEX  5
#define MAX_ADDR 20
#define MAX_TELE 12
//#define MAX_CON  1000
#define DEFAULT  2         //初始通讯录大小
#define INC_COUNT 10       //每次增容大小
#define FILENAME "contact.dat"

typedef struct PeoINFO
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}Peo;
typedef struct Con
{
	Peo *con;
	int count;
	int capacity;
}Con,*pCon;

void Initcon(pCon pcon);
void add(pCon pcon);
void show(pCon pcon);
void del(pCon pcon);
void search(pCon pcon); 
void mod(pCon pcon);
void sort(pCon pcon);
void Exit(pCon pcon);
void destory(pCon pcon);
void Loadcontact(pCon pcon);
void Savecontact(pCon pcon);
#endif  //_CONCATE_H__