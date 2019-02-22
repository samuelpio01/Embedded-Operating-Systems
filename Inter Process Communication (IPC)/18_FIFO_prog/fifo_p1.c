#include "fifo.h"

//p1 ----> writer
int fd;
char str[32];

int main()
{
	int fd;
	char str[32];
	printf("P1: Program started! \n");
	fd= open(FIFO_PATH, O_WRONLY);
	if(fd < 0)
	{
		perror("open() failed");
		_exit(1);
	}

	printf("P1: Enter a message: ");
	fgets(str, sizeof(str), stdin);

	write(fd, str, sizeof(str));
	printf("P1: Message sent.\n");

	close(fd);


	return 0;

}
