#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// ./cat <src_file>

int main(int argc, char* argv[])
{
	int fs, cnt;
	char buff[512];
	//check cmd line args
	if (argc !=2)
	{
		fprintf(stderr, "syntax: %s <src_file>\n",argv[0]);
		_exit(1);
	}
	//open src file for reading
	fs= open(argv[1],O_RDONLY);
	if(fs == -1)
	{
		fprintf(stderr,"syntax: %s file not found",argv[1]);
		_exit(2);
	}

	//read fro src file
	while((cnt= read(fs,buff,sizeof(buff)))>0)
	{
		//write into dest (stdout--> 1) file
		write(1,buff,cnt);

	}	//repeat until end of src file
	
	//close src file
	close(fs);

	return 0;
}
