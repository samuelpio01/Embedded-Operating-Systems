#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// One Parent----> child---> child1--...-->child4

void child_task(int ch)
{
	int i;
	for(i=0;i<5;i++)
	{
		printf("Child[%d] (%d,%d) : %d\n",ch,getpid(),getppid(),i);
		sleep(1);
	}
}

int main()
{
	int i,pid1,pid2,pid3,pid4,s;

	pid1 = fork();
	if(pid1 == 0)
	{
		pid2= fork();
		if(pid2 == 0)
		{
			pid3= fork();
			if(pid3 == 0)
			{
				pid4=fork();
				if(pid4 == 0)
				{
					child_task(4);
					_exit(0);
				}//end of child 4

				child_task(3);
				waitpid(pid4,&s,0);
				printf("Child[4] exit : %d\n",WEXITSTATUS(s));
				_exit(0);
			}//end of child 3

			child_task(2);
			waitpid(pid3,&s,0);
			printf("Child[3] exit : %d\n",WEXITSTATUS(s));
			_exit(0);
		}//end of child 2

		child_task(1);
		waitpid(pid2,&s,0);
		printf("Child[2] exit : %d\n",WEXITSTATUS(s));
		_exit(0);
	}//end of child 1
	

//parent
	for(i=0;i<5;i++)
	{
		printf("parent (%d <--- %d) : %d\n",getpid(),getppid(),i);
		sleep(1);
	}
	
	waitpid(pid1,&s,0);
	printf("Child[1] exit : %d\n",WEXITSTATUS(s));
	
	return 0;
}
