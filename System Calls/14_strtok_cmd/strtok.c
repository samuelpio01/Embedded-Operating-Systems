#include <stdio.h>
#include <string.h>

int main()
{
	char str[]= "This is an example string. Time to tokenize it.";
	char *ptr;
	ptr= strtok(str," ");
	printf("Token = %s\n",ptr);
	do
	{
	ptr = strtok(NULL, " ");
	printf("Token = %s\n",ptr);
	} while(ptr != NULL);

	return 0;
}
