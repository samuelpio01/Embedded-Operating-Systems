#include "1_sun.h"

int main() // client
{
	int cfd, ret;
	struct sockaddr_un svr_addr;
	char buf[64];

	cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(cfd < 0)
	{
		perror("client:socket() failed");
		_exit(1);
	}
	printf("client: connecting socket is ready...\n");

	memset(&svr_addr, 0, sizeof(svr_addr));
	svr_addr.sun_family = AF_UNIX;
	strcpy(svr_addr.sun_path, UNIX_SOCKET_PATH);
	ret = connect(cfd, (struct sockaddr*)&svr_addr, sizeof(svr_addr));
	if(ret < 0)
	{
		perror("client:connect() failed");
		_exit(1);
	}
	printf("client: connected to server...\n");

	do {
		printf("client: ");
		fgets(buf, sizeof(buf), stdin);
		write(cfd, buf, strlen(buf)+1);

		read(cfd, buf, sizeof(buf));
		printf("server: %s", buf);
	} while(strcmp(buf, "bye\n") != 0);

	close(cfd);
	printf("client: good bye!\n");
	return 0;
}

