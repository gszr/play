#include "local.h"

#define BACKLOG 10

int
main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	uint8_t buf[BUF_SIZE];
	int sfd, cfd;
	ssize_t nrd;

	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		error(1, errno, "could not create socket");

	if (remove(SOCK_NAME) == -1)
		error(0, errno, "could not remove '%s'", SOCK_NAME);

	memset(&addr, 0, sizeof(addr));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_NAME, sizeof(addr.sun_path) - 1);

	if (bind(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
		error(1, errno, "could not bind socket to '%s'", SOCK_NAME);

	if (listen(sfd, BACKLOG) == -1)
		error(1, errno, "could not put socket to listen");

	for(;;) {

		if ((cfd = accept(sfd, NULL, NULL)) == -1)
			error(1, errno, "could not accept connection");

		while ((nrd = read(cfd, buf, BUF_SIZE)) > 0)
			if (write(STDOUT_FILENO, buf, nrd) != nrd)
				error(1, errno, "partial or failed write");

		if (nrd == -1)
			error(1, errno, "error on read");

		if (close(cfd) == -1)
			error(1, errno, "error on close");
	}

	return EXIT_SUCCESS;
}
