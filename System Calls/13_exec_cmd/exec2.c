#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int ret,s,err;
	char *envp[] = {"USER= Bhoko","HOME=/home/cdac/","TEST = This is where I end when I'm bored",NULL};
	printf("parent started\n");
	printf("parent calling execle()...\n");
	ret = fork();
	if(ret ==0)
	{
		err = execle("./child","child", NULL, envp);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}

	waitpid(ret, &s, 0);
	printf("\nparent calling execve()\n");
	ret= fork();
	if(ret == 0)
	{
		char *args[]= {"child",NULL};
		err = execve("./child",args,envp);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
		_exit(1);
	}
	waitpid(ret, &s, 0);

	printf("Parent finished! \n");

	return 0;
}
