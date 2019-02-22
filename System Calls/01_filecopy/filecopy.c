#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//syntax: ./filecopy <src file> <dest file>


int main(int argc, char *argv[])
{
	int fs,fd,cnt;
	char buff[512];
	
	//check cmd lines
	if(argc!=3)
	{
		fprintf(stderr,"syntax: %s <src_file <dest_file>\n",argv[0]);
		_exit(1);
	}
	
	//open src file for reading
	fs= open(argv[1],O_RDONLY);
	if(fs == -1)
	{
		perror("open() failed for src file");
		_exit(2);
	}

	//open dest file for writing
	fd= open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0644); //0644 is permissions in ocatal
	if(fd == -1)
	{
		perror("open() failed for dest file");
		close(fs);
		_exit(3);
	}

	//read from src file
	while((cnt=read(fs,buff,sizeof(buff)))>0)
	{
		//write into dest file
		write(fd,buff,cnt);

	}	//repeat until end of src file
	
	//close dest file
	close(fd);
	
	//close src file
	close(fs);

	printf("Files copied successfully");

	return 0;
}
