#include "semaphore2.h"

void sunbeam()
{
	char *s = "SUNBEAM\n";
	int i;
	for(i=0; s[i]!='\0'; i++)
	{
		putchar(s[i]);
		fflush(stdout);
		sleep(1);
	}
}

int sem_init()
{
	int semid, ret;
	semun_t su;

	//check if semaphore is already created
	semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
	if(semid < 0)
	{
		//if already present, then return its id
		if(errno == EEXIST)
		{
			semid = semget(SEM_KEY, 1, 0);
			return semid;
		}
		else
		{
			perror("semget() failed");
			_exit(0);
		}
	}
	//if new created, init it to 0 :: s=0
	su.val = 0;
	ret = semctl(semid, 0, SETVAL, su);
	//err check..
	return semid;
}

int main()
{
	int semid, ret;
	struct sembuf sops[1];

	semid = sem_init();
	sunbeam();
	//V(s)
	sops[0].sem_num = 0;
	sops[0].sem_op = +1;
	sops[0].sem_flg = 0;
	ret = semop(semid, sops, 1);

	return 0;
}
