#include "65_sin.h"

int lsfd;

void sigint_handler(int sig)
{
	printf("server: good bye!\n");
	shutdown(lsfd, SHUT_RDWR);
	_exit(0);
}

void sigchld_handler(int sig)
{
	int s;
	waitpid(-1, &s, 0);
}

void strupr(char *s)
{
	int i;
	for(i=0; s[i] != '\0'; i++)
	{
		s[i] = toupper(s[i]);
		putchar(s[i]);
		fflush(stdout);
		sleep(1);
	}
	putchar('\n');
}

int main() // server
{
	int fd, ret, pid;
	struct sockaddr_in svr_addr, cli_addr;
	socklen_t len = sizeof(cli_addr);
	char buf[64];
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);
	// err check ...

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigchld_handler;
	ret = sigaction(SIGCHLD, &sa, NULL);
	// err check ...
	
	lsfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lsfd < 0)
	{
		perror("server:socket() failed");
		_exit(1);
	}
	printf("server: listening socket is ready...\n");

	memset(&svr_addr, 0, sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(SVR_PORT);
	inet_aton(SVR_IP, &svr_addr.sin_addr);
	ret = bind(lsfd, (struct sockaddr*)&svr_addr, sizeof(svr_addr));
	if(ret < 0)
	{
		perror("server:bind() failed");
		_exit(1);
	}
	printf("server: listening socket addr assigned...\n");

	listen(lsfd, 5);

	while(1)
	{
		memset(&cli_addr, 0, sizeof(cli_addr));
		fd = accept(lsfd, (struct sockaddr*)&cli_addr, &len);
		if(fd < 0)
		{
			if(errno == EINTR)
				continue;
			perror("server:accept() failed");
			_exit(1);
		}

		pid = fork();
		if(pid == 0)
		{
			read(fd, buf, sizeof(buf));
			printf("client: %s\n", buf);

			strupr(buf);
			write(fd, buf, strlen(buf)+1);

			close(fd);
			_exit(0);
		}
		else
			close(fd);
	}
	return 0;
}

