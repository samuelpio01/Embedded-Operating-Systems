#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int ret, arr[2], pid, s;
	char buff1[32], buff2[32];

	ret = pipe(arr);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(1);
	}

	pid = fork();
	if(pid == 0)
	{// child ---- writer
		close(arr[0]);  //closed bacuse of multiple inputs and outputs created because of fork copy of inode count

		printf("Child: Enter a message :");
		fgets(buff1, sizeof(buff1), stdin);

		write(arr[1], buff1, sizeof(buff1));
		printf("Child: written into the pipe\n");

		close(arr[1]);
	}
	else
	{// parent ---- reader
		close(arr[1]); //closed bacuse of multiple inputs and outputs created because of fork copy of inode count

		printf("Parent: waiting for message.. \n");

		read(arr[0], buff2, sizeof(buff2));
		printf("Parent: read from pipe : %s\n",buff2);

		waitpid(pid, &s, 0);
		close(arr[0]);
	}

	return 0;
}
