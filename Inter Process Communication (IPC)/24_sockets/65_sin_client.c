#include "65_sin.h"

int main(int argc, char *argv[]) // client
{
	int cfd, ret;
	struct sockaddr_in svr_addr;
	char buf[64];

	if(argc != 2)
	{
		printf("syntax: %s <string>\n", argv[0]);
		_exit(1);
	}

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd < 0)
	{
		perror("client:socket() failed");
		_exit(1);
	}
	printf("client: connecting socket is ready...\n");

	memset(&svr_addr, 0, sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(SVR_PORT);
	inet_aton(SVR_IP, &svr_addr.sin_addr);
	ret = connect(cfd, (struct sockaddr*)&svr_addr, sizeof(svr_addr));
	if(ret < 0)
	{
		perror("client:connect() failed");
		_exit(1);
	}
	printf("client: connected to server...\n");

	write(cfd, argv[1], strlen(argv[1])+1);

	read(cfd, buf, sizeof(buf));
	printf("result: %s\n", buf);

	close(cfd);
	return 0;
}

