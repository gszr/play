/* from TLPI */

#include <sys/un.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdint.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define SOCK_NAME "/tmp/local_socket"
#define BUF_SIZE  1024
