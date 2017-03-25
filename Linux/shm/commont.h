#ifndef _COMMONT_
#define _COMMONT_
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define PATHNAME "."
#define PROJID 88
#define SIZE 4096*1

int CreatShm();
int GetShm();
int DestoryShm();
int dtShm(const void* arg);
#endif
