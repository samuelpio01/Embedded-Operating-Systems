#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct data
{
	int cnt;
}data_t;

data_t var;

int main()
{
	int pid, i, s;

	//init the count
	var.cnt=0;

	pid = fork();
	if(pid == 0)
	{
		for(i=0; i<10; i++)
		{
			var.cnt++;
			printf("child : %d\n",var.cnt);
			sleep(1);
		}
		_exit(0);
	}
	else
	{
		for(i=0; i<10; i++)
		{
			var.cnt--;
			printf("parent : %d\n",var.cnt);
			sleep(1);
		}
		waitpid(pid, &s, 0);
		printf("final count : %d\n",var.cnt);
	}

	return 0;
}
