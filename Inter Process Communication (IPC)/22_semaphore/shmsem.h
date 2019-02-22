#ifndef __SHMSEM_H
#define __SHMSEM_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "3_cirq.h"

#define SHMKEY	0x4512
#define SEMKEY	0x2154

typedef struct
{
	cirque_t cq;
}shm_t;

typedef union semun 
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
}semun_t;

#define MUT	0
#define FIL 1
#define EMP	2

#endif
