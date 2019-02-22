#include <stdio.h>
#include <unistd.h>

//happens because of printf() buffer
//flushes only when the buffer is full or it encounters '\n'

int main()
{
	printf("\nstart ");
	fork();
	printf("end \n");
	return 0;
}
