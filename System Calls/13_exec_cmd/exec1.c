#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ret,s,err;
	printf("parent started! \n");
	printf("parent calling execl()  \n");
	ret= fork();
	if(ret == 0)
		{
		//execl("file_path","file_name","cmdline_arg1","cmdline_arg2",...);
			err=execl("./dir","dir",".",NULL);
			if(err < 0)
			{
				perror("exec() failed");
				_exit(1);
			}
		}

		waitpid(ret, &s, 0);
		printf("\nparent calling execv()...\n");
		ret= fork();
		if(ret == 0)
		{
			char *args[]= {"pattern6","ONE","TWO",NULL};
			err= execv("./pattern6",args);
			if(err<0)
			{
				perror("exec() failed");
				_exit(1);
			}
		}
		waitpid(ret,&s,0);

		printf("parent finished \n");
		return 0;
}
