#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define MQ_KEY	0x2809
#define MT_C2P	1332

typedef struct msg
{
	long type;
	char data[20];
}msg_t;

void sigint_handler(int sig)
{
	printf("SIGINT received....\n");
}

int main()
{
	int ret, s, pid, mqid;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	//create msg queue
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0)
	{
		perror("msgget() failed");
		_exit(1);
	}

	pid = fork();
	if(pid == 0)
	{//child -----> sender
		msg_t m1;
		//take user input
		printf("Parent: waiting for the message..\n");
		fgets(m1.data, sizeof(m1.data), stdin);

		//send msg
		m1.type = MT_C2P;
		ret = msgsnd(mqid, &m1, sizeof(m1.data),0);
		printf("Child: msg sent with ret value = %d\n",ret);
		_exit(0);
	}
	else
	{
		msg_t m2;
		printf("Parent: waiting for the message...\n");

		//receive msg
		ret = msgrcv(mqid, &m2, sizeof(m2.data),MT_C2P,0);
		if (ret < 0)
			perror("msgrcv() failed");
		else
			printf("Parent: Message received : %s\n",m2.data);

		waitpid(pid, &s, 0);

		msgctl(mqid, IPC_RMID,NULL);// to destroy contents from ipcs
				
	}

	return 0;
}
