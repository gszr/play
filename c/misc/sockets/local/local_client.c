#include "local.h"

int
main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	uint8_t buf[BUF_SIZE];
	ssize_t nrd;
	int sfd;

	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		error(1, errno, "could not create socket");

	memset(&addr, 0, sizeof(addr));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_NAME, sizeof(addr.sun_path) - 1);

	if (connect(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
		error(1, errno, "could not connect to server");

	while ((nrd = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
		if (write(sfd, buf, nrd) != nrd)
			error(1, errno, "partial or failed write");

	if (nrd == -1)
		error(1, errno, "error on read");

	return EXIT_SUCCESS;
}
