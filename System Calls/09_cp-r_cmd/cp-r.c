#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

//syntax: ./cp-r <source> <destination>


int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *de;
	struct stat sb;
	int fs,fd,cnt,ret;
	char buff[512];
	
	//check cmd lines
	if(argc!=3)
	{
		fprintf(stderr,"syntax: %s <src_file <dest_file> \n",argv[0]);
		_exit(1);
	}

	//make new Directory in dest address
	fd= mkdir(argv[2],0777);
	if(fd < 0)
	{
		perror("mkdir() failed\n");
		_exit(4);
	}

	//change current directory
	printf("outside chdir\n");
	ret= chdir(argv[1]);
	printf("inside chdir\n");
	if(ret < 0)
	{
		perror("Cannot access given directory\n");
		_exit(5);
	}

	//open dir
	dp= opendir(argv[1]);
	if(dp==NULL)
	{
		perror("opendir() failed");
		_exit(6);
	}

	//get directory entry from source 
	while((de=readdir(dp))!=NULL)
{	
	printf("inside while loop\n");
	//open src file for reading
	fs= open(de->d_name,O_RDONLY);
	if(fs == -1)
	{
		perror("open() failed for src file\n");
		_exit(2);
	}

	//open dest file for writing
	fd= open(de->d_name,O_WRONLY|O_TRUNC|O_CREAT,0644); //0644 is permissions in ocatal
	if(fd == -1)
	{
		perror("open() failed for dest file\n");
		close(fs);
		_exit(3);
	}

	//read from src file	
	while((cnt=read(fs,buff,sizeof(buff)))>0)
	{

		//write into dest file
		write(fd,buff,cnt);

	}	//repeat until end of src files
	
	//close dest file
	close(fd);
	
	//close src file
	close(fs);
}
	printf("Files copied successfully\n");

	return 0;
}
