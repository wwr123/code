#ifndef __COMMON_H__
#define __COMMON_H__
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#define PATHNAME "."
#define PROJID 99

 union semun {
              int val;    /* Value for SETVAL */
			  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	          unsigned short  *array;  /* Array for GETALL, SETALL */
		      struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */	            };

int CreatSemSet(int nums);
int GetSemSet();
int DestorySemSet(int semid);
int P(int semid,int which);
int V(int semid,int which);
int InitSemSet(int semid,int which);
#endif
