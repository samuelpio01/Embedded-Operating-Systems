#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

//syntax: 	./mkdir <dir_name>

int main(int argc,char * argv[])
{
	int fd;
	
	if(argc!=2)
	{
		fprintf(stderr,"syntax: %s <dir_name>",argv[0]);
		_exit(1);
	}

	fd= mkdir(argv[1],0777);
	if(fd < 0)
	{
		perror("mkdir() failed");
		_exit(2);
	}

	return 0;
}
