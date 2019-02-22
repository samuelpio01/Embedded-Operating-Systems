#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

//	./stat <path>

int main(int argc,char* argv[])
{
	int ret;
	struct stat sb;

	//check cmdline args
	if (argc!=2)
	{
		fprintf(stderr,"syntax: %s <path>\n",argv[1]);
		_exit(1);
	}

	//get file/dir info (stat syscall)
	ret=stat(argv[1],&sb);
	if(ret<0)
	{
		perror("stat() failed");
		_exit(2);
	}

	//display that info
	printf("Name : %s \n",argv[1]);
	printf("Inode : %lu \n",sb.st_ino);
	printf("Mode : %#o\n",sb.st_mode);
	printf("Number of Hardlinks : %d\n",sb.st_nlink);
	printf("User ID : %u \n" ,sb.st_uid);
	printf("Group ID : %u\n",sb.st_gid);
	printf("Size : %lu\n",sb.st_size);
	printf("IO blocksize : %ld\n",sb.st_blksize);
	printf("Number of Sectors : %lu\n",sb.st_blocks);


	return 0;
}

