#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/socket.h>
#include <linux/tcp.h>
#include <sys/fcntl.h>
#include <errno.h>

#ifndef SOL_TCP
#define SOL_TCP 6
#endif


int main()
{
	printf("hello world\n");
	printf("THIS IS FROM INSIDE OF JUNCTION\n");
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		fprintf(stderr, "Failed to craete a socket\n");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.127.3", &(addr.sin_addr));
	addr.sin_port = htons(8080);

	socklen_t addr_len =  sizeof(addr);
	int ret = bind(fd, (struct sockaddr *)&addr, addr_len);
	if (ret != 0) {
		perror("failed to bind\n");
		return 1;
	}
	ret = listen(fd, 10);
	if (ret != 0) {
		perror("failed to listen\n");
		printf("fd: %d (errno %d)\n", fd, errno);
		return 1;
	}

	int flags = 0;
	int optval = 1;
	socklen_t optlen = sizeof(optval);
	setsockopt(fd, SOL_TCP,    TCP_NODELAY,  &optval, optlen);
	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, optlen);
	flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		fprintf(stderr, "Something is wrong with the flag\n");
		return 1;
	}
	ret = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (ret < 0) {
		fprintf(stderr, "Failed to set the O_NONBLOCK\n");
		return 1;
	}

	while(1) {
		int cfd = accept(fd, NULL, NULL);

		if (cfd < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				continue;
			}
			perror("accept failed\n");
			continue;
		}

		printf("Received a connection\n");
		fflush(stdout);
		/* handle connection */
		while (1) {
			char buf[256];
			int len = recv(cfd, buf, 256, 0);
			if (len == 0) {
				printf("end of connection!\n");
				break;
			}
			if (len < 0) {
				if (errno == EAGAIN)
					continue;
				perror("Something failed!\n");
				break;
			}
			buf[len] = 0;
			printf("recv (%d): %s\n", len, buf);
			fflush(stdout);
			send(cfd, "ACK\n", 4, 0);
		}
		printf("End of the connection\n");
		fflush(stdout);
	}
}
