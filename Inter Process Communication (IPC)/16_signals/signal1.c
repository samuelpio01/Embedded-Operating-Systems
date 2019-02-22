#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//step1: Implement signal handler

void sigint_handler(int sig)
{
	printf("SIGINT --- signal caught: %d\n",sig);
}

void sigterm_handler(int sig)
{
	printf("SIGTERM --- signal caught: %d\n",sig);
}
void sighup_handler(int sig, siginfo_t *si, void *param)
{
	printf("SIGHUP --- signal caught: %d\nSender process : %d\n",sig,si->si_pid);
}

int main()
{
	int ret, i=0;
	struct sigaction sa1, sa2;

	//step 2: register signal handler
	memset(&sa2, 0 ,sizeof(sigaction));
	memset(&sa1, 0 ,sizeof(sigaction));
	sa1.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa1, &sa2);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}
	
	memset(&sa2, 0, sizeof(sigaction));
	memset(&sa1, 0, sizeof(sigaction));
	sa1.sa_sigaction=  sighup_handler;
	sa1.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGHUP, &sa1, &sa2);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	memset(&sa2, 0, sizeof(sigaction));
	memset(&sa1, 0, sizeof(sigaction));
	sa1.sa_handler = sigterm_handler;
	ret = sigaction(SIGTERM, &sa1, &sa2);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	while(1)
	{
		printf("Running [%d] : %d\n",getpid(), i++);	
		sleep(1);
	}

	return 0;
}
