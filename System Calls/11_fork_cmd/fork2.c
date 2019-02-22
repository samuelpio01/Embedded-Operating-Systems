#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ret,i,s;
	printf("Program has begun\n");
	ret= fork();
	if(ret==0)
	{
		for(i=0;i<6;i++)
		{
			printf("Child : %d\n",i);
			sleep(1);
		}
	}
	else
	{
		for(i=0;i<11;i++)
		{
			printf("Parent : %d\n",i);
			sleep(1);
			if(i==5)
			{
				wait(&s);
				printf("child exit status : %d.\n",WEXITSTATUS(s));
			}
		}
	}
	printf("Program has ended\n");

	return 0;
}
