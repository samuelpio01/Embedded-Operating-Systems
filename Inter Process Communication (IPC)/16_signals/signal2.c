#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	sigset_t newmask, oldmask;
	int ret, i=0;

	//block SIGINT & SIGTERM
	sigemptyset(&oldmask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGTERM);

	ret = sigprocmask(SIG_SETMASK, &newmask, &oldmask);
	if(ret < 0)
	{
		perror("sigprocmask() failed");
		_exit(1);
	}

	while(1)
	{
		printf("Running : %d \n", ++i);
		sleep(1);
	}
	return 0;
}
