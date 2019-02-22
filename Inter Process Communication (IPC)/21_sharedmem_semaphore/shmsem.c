#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

//implement mutual exclusion using semaphore

#define SHM_KEY 0x2809
#define SEM_KEY 0x1565

typedef union semun 
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
}semun_t;

typedef struct data
{
	int cnt;
}data_t;

int shmid, semid;
data_t *ptr;

void sigint_handler()
{
	semctl(semid, 0, IPC_RMID);
	_exit(0);
}

int main()
{
	int ret,pid,i,s;
	struct sigaction sa;
	semun_t su;
	struct sembuf sops[1];

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);
	if (ret < 0)
	{
		perror("sigaction() failed");
		_exit(0);
	}

	//create semaphore with single counter.
	semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
	if(semid < 0)
	{
		perror("semget() failed");
		_exit(0);
	}

	//init sema cntr to "1"
	su.val = 1;
	ret = semctl(semid, 0, SETVAL, su);
	if (ret < 0)
	{
		perror("semctl() failed");
		semctl(semid, 0, IPC_RMID);
		_exit(0);
	}

	//create shared memory
	shmid = shmget(SHM_KEY, 1, IPC_CREAT | 0600);
	if (shmid < 0)
	{
		perror("shmget() failed");
		semctl(semid, 0, IPC_RMID);
		_exit(0);
	}

	//get ptr to shared memory region
	ptr = shmat(shmid, NULL, 0);
	if(ptr == (void *)-1)
	{
		perror("shmat() failed");
		shmctl(shmid, IPC_RMID, NULL);
		semctl(shmid, 0, IPC_RMID);
		_exit(0);
	}

	//intialize the count
	ptr->cnt = 0;

	//mark shm for deletion
	ret = shmctl(shmid, IPC_RMID, NULL);


	pid = fork();
	if(pid == 0)
	{//child incr count
		for(i=0; i<10; i++)
		{
			//P(s)
			sops[0].sem_num = 0;
			sops[0].sem_op = -1;
			sops[0].sem_flg = 0;
			ret = semop(semid,sops,1);
			if(ret < 0)
			{
				perror("semop() failed");
				_exit(0);
			}

			ptr->cnt++;
			printf("child : %d\n",ptr->cnt);

			// V(s);
 			sops[0].sem_num = 0;
			sops[0].sem_op = +1;
			sops[0].sem_flg = 0;
			ret = semop(semid, sops, 1);

			sleep(1);
		}
		shmdt(ptr);
		_exit(1);
	}
	else
	{//parent decrement count
		for(i=0; i<10; i++)
		{
		//P(s)
		sops[0].sem_num = 0;
		sops[0].sem_op = -1;
		sops[0].sem_flg = 0;
		ret= semop(semid, sops, 1);

		ptr->cnt--;
		printf("parent : %d\n",ptr->cnt);

		//V(s)
		sops[0].sem_num = 0;
		sops[0].sem_op = +1;
		sops[0].sem_flg = 0;
		ret= semop(semid, sops, 1);
		
		sleep(1);
		}
		waitpid(pid, &s, 0);
		printf("final count : %d\n", ptr->cnt);

		//release ptr of shared mem region
		shmdt(ptr);
		semctl(semid, 0, IPC_RMID);
	}

	return 0;
}
