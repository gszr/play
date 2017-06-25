#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int
main(int argc, char **argv)
{
	int sfd, cfd;
	struct sockaddr_in addr_me;
	char buff[512] = {'\0'};
	
	sfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&addr_me, 0, sizeof(addr_me));
	addr_me.sin_family = AF_INET;
	addr_me.sin_port = htons(8080);
	addr_me.sin_addr.s_addr = inet_addr("192.168.33.1");

	bind(sfd, (struct sockaddr*)&addr_me, sizeof(struct sockaddr));
	read(sfd, buff, sizeof(buff));

	printf("recvd: %s\n", buff);

	close(sfd);
	return 0;
}
