#include "fifo.h"

//P2 ----> reader

int main()
{
	int fd;
	char str[32];
	printf("P2: Program started\n");
	fd= open(FIFO_PATH, O_RDONLY);
	if(fd < 0)
	{
		perror("open() failed");
		_exit(1);
	}

	printf("P2: Waiting to read");

	read(fd, str, sizeof(str));
	printf("P2: Message received: %s.",str);

	close(fd);
	

	return 0;
}
