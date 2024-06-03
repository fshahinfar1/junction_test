#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>


int main()
{
	printf("hello world\n");
	printf("THIS IS FROM INSIDE OF JUNCTION\n");
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		fprintf(stderr, "Failed to craete a socket\n");
		return 1;
	}


	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	/* inet_pton(AF_INET, "192.168.127.3", &(addr.sin_addr)); */
	inet_pton(AF_INET, "192.168.200.101", &(addr.sin_addr));
	addr.sin_port = htons(8080);

	socklen_t addr_len =  sizeof(addr);
	int ret = bind(fd, (struct sockaddr *)&addr, addr_len);
	if (ret != 0) {
		perror("failed to bind\n");
		return 1;
	}
	while (1) {
		char buf[256];
		struct sockaddr_in client;
		socklen_t client_addr_len;
		size_t len = recvfrom(fd, buf, 256, 0, (struct sockaddr *)&client, &client_addr_len);
		if (len == 0) {
			printf("end of connection!\n");
			break;
		}
		/* buf[len] = 0; */
		/* printf("recv: %s\n", buf); */
		/* fflush(stdout); */
		/* sendto(fd, "ACK\n", 4, 0, (struct sockaddr *)&client, client_addr_len); */
		sendto(fd, buf, len, 0, (struct sockaddr *)&client, client_addr_len);
	}
}
