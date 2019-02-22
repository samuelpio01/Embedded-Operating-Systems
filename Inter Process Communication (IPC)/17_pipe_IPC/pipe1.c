#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret, arr[2];
	char buff1[32], buff2[32];

	ret = pipe(arr);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(1);
	}

	printf("Enter a message : ");
	fgets(buff1, sizeof(buff1),stdin);

	write(arr[1], buff1, sizeof(buff1));
	printf("Written into pipe : %s\n",buff1);

	read(arr[0],buff2, sizeof(buff2));
	printf("Read from pipe : %s\n",buff2);

	close(arr[1]);
	close(arr[0]);

	return 0;
}
