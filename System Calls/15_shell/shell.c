#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	char cmd[1024], *ptr, *args[32];
	int i, ret, s, err;

	while(1)
	{
		printf("cmd> ");
		fgets(cmd, sizeof(cmd),stdin);
		i=0;
		ptr = strtok(cmd," \t\n");
		args[i++] = ptr;
		do{
			ptr= strtok(NULL," \t\n");
			args[i++] = ptr;
		}while(ptr != NULL);
		
		if(strcmp(args[0], "exit")==0)
			_exit(0);
		else if(strcmp(args[0],"cd")==0)
			chdir(args[1]);
		else
		{
			ret = fork();
			if(ret == 0)
			{
				err= execvp(args[0],args);
				if(err < 0)
				{
					perror("bad command");
					_exit(1);
				}
			}
			waitpid(ret , &s, 0);
		}
		
	}

	return 0;
}
