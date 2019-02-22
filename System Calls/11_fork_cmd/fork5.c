#include <stdio.h>
#include <unistd.h>

int main()
{	
	fork();
	printf("Bapui tuzo!\n");
	fork();
	printf("Maami tuzi!\n");
	fork();
	printf("Yo mama!\n");
	return 0;
}
