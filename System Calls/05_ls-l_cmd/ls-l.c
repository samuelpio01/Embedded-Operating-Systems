#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

// ./ls-l <dirpath>


int main(int argc,char * argv[] )
{
	DIR *dp;
	int ret;
	struct dirent *de;
	struct stat sb;
	char buff[512];

	//check cmd line args
	if (argc!=2)
	{
		fprintf(stderr,"syntax: %s <dir_path>",argv[0]);
		_exit(0);
	}

	//go to the given dir
	ret= chdir(argv[1]);
	if(ret < 0)
	{
		perror("Cannot access given directory");
		_exit(1);
	}

	//open dir
	dp= opendir(argv[1]);
	if(dp==NULL)
	{
		perror("opendir() failed");
		_exit(2);
	}

	//get next dirent and print it
	while((de= readdir(dp))!= NULL)
	{
		ret = stat(de->d_name,&sb);
		if(ret < 0)
		{
			perror("stat() failed");
			continue;
		}
		printf("|%10lu|%6o|%4d|%8u|%8u|%15lu|%20s\n",
		de->d_ino, sb.st_mode, sb.st_nlink, sb.st_uid, sb.st_gid, sb.st_size, de->d_name);
	}	//repeat until all entiries are done

	//close dir
	closedir(dp);


	return 0;
}
