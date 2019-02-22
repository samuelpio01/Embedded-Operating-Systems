#include <stdio.h>
#include <unistd.h>

//cmd line arg parameters changed just to check (instead of argv[] and argc)

int main(int constant,char *array[],char *envp[] )
{
	int i;
	for(i=0; array[i]!=NULL;i++)
	{
		printf("Child :%s| %d\n",array[i],constant);
	}

	return 0;
}
