#include "1_sun.h"

int main()
{
	int lsfd, fd, ret;

	struct sockaddr_un svr_addr, cli_addr;
	socklen_t len = sizeof(cli_addr);
	char buff[64];

	
	lsfd = socket(AF_UNIX, SOCK_STREAM,0);
	if(lsfd<0)
	{
		perror("server:socket() failed\n");
		_exit(1);
	}
	printf("server: listening socket is ready...\n");

	memset(&svr_addr,0,sizeof(svr_addr));
	svr_addr.sun_family = AF_UNIX;
	strcpy(svr_addr.sun_path, UNIX_SOCKET_PATH);
	ret = bind(lsfd, (struct socaddr*)&svr_addr, sizeof(svr_addr));
	if(ret<0)
	{
		perror("Server: bind() faield");
		_exit(1);
	}
	printf("Server: listening socket addr assigned..\n");

	listen(lsfd, 5);
	
	memset(&cli_addr, 0, sizeof(cli_addr));
	fd = accept(lsfd, (struct sockaddr*)&cli_addr,&len);
	if(fd < 0)
	{
		perror("Server: accept() failed");
		_exit(1);
	}
	printf("Server: Client connection accepted..\n");

	do
	{
		read(fd, buff, sizeof(buff));
		printf("Client: %s\n",buff);
		fgets(buff, sizeof(buff),stdin);
		write(fd, buff, strlen(buff)+1);
	}while(strcmp(buff, "bye\n") !=0 );

	close(fd);
	printf("Server: good bye");
	shutdown(lsfd, SHUT_RDWR);
	unlink(UNIX_SOCKET_PATH);
	
	return 0;
}
