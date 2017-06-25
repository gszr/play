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
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&addr_me, 0, sizeof(addr_me));
	addr_me.sin_family = AF_INET;
	addr_me.sin_port = htons(8080);
	addr_me.sin_addr.s_addr = inet_addr("192.168.33.1");

	if(connect(sfd, (struct sockaddr*) &addr_me, sizeof addr_me)) printf("oops\n");
	char *str = "ola kernel lua world";
	write(sfd, str, strlen(str));

	close(sfd);
	return 0;
}
