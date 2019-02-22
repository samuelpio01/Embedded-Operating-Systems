#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ret, s, err;
	printf("parent started\n");

	//ls -l -a /home
	
	ret = fork();
	if(ret == 0)
	{
		err= execlp("ls","ls","-l","-a", NULL);
		if (err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}

	waitpid( ret, &s, 0);
	printf("child exit status : %d\n",WEXITSTATUS(s));
	printf("parent finished execution\n");

	return 0;
}
