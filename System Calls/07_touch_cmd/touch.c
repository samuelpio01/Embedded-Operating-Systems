#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
// ./touch <file_path>

int main(int argc, char *argv[])
{
	int fd;
	if(argc!=2)
	{
		fprintf(stderr,"syntax: %s <file_path>\n",argv[0]);
		_exit(1);
	}
	
	fd= open(argv[1],O_WRONLY|O_CREAT,0777);
	if(fd<0)
	{
		perror("open() faiiled");
		_exit(2);
	}

	close(fd);
	
	return 0;
}
