#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// One Parent----> multiple child

void child_task(int ch)
{
	int i;
	for(i=0;i<5;i++)
	{
		printf("Child[%d] (%d) : %d\n",ch,getpid(),i);
		sleep(1);
	}
}

int main()
{
	int i,ret,s;

	for(i=0;i<5;i++)
	{
		ret = fork();
		if(ret == 0)
		{
			//child
			child_task(i);
			_exit(i);
		}
	}

	for(i=0;i<3;i++)
	{
		printf("parent (%d) : %d\n",getpid(),i);
		sleep(1);
	}
		
		
	printf("parent : waiting for all child processes...\n");

	for(i=0;i<5;i++)
	{
		ret= waitpid(-1, &s, 0);
		printf("Child[%d] exit : %d\n",ret,WEXITSTATUS(s));
	}
	
	printf("parent : cleaned up all child processes...\n");
	
	return 0;
}
