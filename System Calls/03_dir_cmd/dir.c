#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

//	./dir <dir_path>

int main (int argc, char* argv[])
{
	DIR *dp;
	struct dirent *de;

	//check cmd line args
	if(argc != 2)
	{
		fprintf(stderr,"syntax: %s <dir_path>\n",argv[0]);
		_exit(1);
	}
	
	//open dir
	dp = opendir(argv[1]);
	if (dp == NULL)
	{
		perror("opendir() failed");
		_exit(2);
	}
	
	//get next directory entry and print it
	while((de= readdir(dp))!=NULL)
		{
			printf("%4lu \t %4s\n",de->d_ino,de->d_name);
		}	//repeat until all entries are done

	//close directory
	closedir(dp);

	return 0;
}
