#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/inotify.h>

#define BUFF_LEN (sizeof(struct inotify_event) + NAME_MAX + 1)

static int loop(int inot_fd);
static int copyFile(struct inotify_event *event);
static int deleteFile(struct inotify_event *event);

static const char *srcDirName;
static const char *dstDirName;
static char myworkdir[PATH_MAX];

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s dir1 dir2\n\tdir1: source \
				diretory\n\tdir2: destination directory\n",
				argv[0]);
		return(EXIT_FAILURE);
	}

	srcDirName = argv[1];
	dstDirName = argv[2];

	if (!getcwd(myworkdir, PATH_MAX)) {
		fprintf(stderr, "getcwd error\n");
		return EXIT_FAILURE;
	}


	int inot_fd;
	if ((inot_fd = inotify_init()) == -1) {
		fprintf(stderr, "inotify_init error\n");
		return EXIT_FAILURE;
	}

	int inot_wd;
	if ((inot_wd = inotify_add_watch(inot_fd, srcDirName, IN_CREATE | IN_DELETE)) == -1) {
		fprintf(stderr, "inotify_add_watch error\n");
		return EXIT_FAILURE;
	}

	printf("Watching %s\n", srcDirName);

	loop(inot_fd);

	return EXIT_SUCCESS;
}

	static int 
loop(int inot_fd)
{
	struct inotify_event *event;
	char buff[BUFF_LEN];
	ssize_t nread;

	for(;;) {
		if ((nread = read(inot_fd, buff, BUFF_LEN)) <= 0) {
			fprintf(stderr, "read error\n");
			return(EXIT_FAILURE);
		}

		event = (struct inotify_event *) buff;

		if (event->mask & IN_CREATE)
			copyFile(event);
		else if (event->mask & IN_DELETE)
			deleteFile(event);
	}

	return 1;
}

	static int
copyFile(struct inotify_event *event)
{
	FILE *srcFp, *dstFp;
	char buff[512];

	if (chdir(srcDirName) == -1)
		return 0;

	if (!(srcFp = fopen(event->name, "rb")))
		return 0;

	if (chdir(myworkdir) == -1) {
		fclose(srcFp);
		return 0;
	}

	if (chdir(dstDirName) == -1) {
		fclose(srcFp);
		return 0;
	}

	if (!(dstFp = fopen(event->name, "wb"))) {
		fclose(srcFp);
		return 0;
	}

	if (chdir(myworkdir) == -1) {
		fclose(srcFp);
		fclose(dstFp);
		return 0;
	}

	printf("Copying '%s/%s' to '%s/%s'... ", srcDirName, event->name, dstDirName, 
			event->name);

	int nread;
	while ((nread = fread(buff, 1, 512, srcFp)) > 0) {

		if (fwrite(buff, nread, 1, dstFp) == 0 && ferror(dstFp) != 0) {
			fprintf(stderr, "fwrite error\n");
			fclose(srcFp);
			fclose(dstFp);
			return 0;
		}
	}

	if (ferror(srcFp) != 0) {
		fprintf(stderr, "fread error\n");
		fclose(srcFp);
		fclose(dstFp);
		return 0;;
	}

	printf("OK\n");

	fclose(srcFp);
	fclose(dstFp);

	return 1;
}

	static int
deleteFile(struct inotify_event *event)
{
	printf("Removing '%s/%s'... ", dstDirName, event->name);
	if (chdir(dstDirName) == -1)
		return 0;
	if (remove(event->name) != 0) {
		chdir(myworkdir);
		printf("Could not remove '%s/%s'\n", dstDirName, event->name);
		return 0;
	}
	if (chdir(myworkdir) == -1)
		return 0;
	printf("OK\n");
	return 1;
}
