/* Little program to test (and learn to use) getopt(3) */

#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	int ch;
	while ((ch = getopt(argc, argv, "bf:o::")) != -1) {
		switch(ch) {
			case 'b':
				printf("Simple option 'b' passed\n");
				break;
			case 'f':
				printf("Option 'b' passed; option argument is '%s'\n",
						optarg);
				break;
			case 'o':
				printf("Option 'b' passed; optional argument is '%s'\n",
						optarg);
				break;
			case '?':
				printf("Unknown option\n");
		}
	}

	argv += optind;
	argc -= optind;

	printf("%d arguments remaining\n", argc);

	return 0;
}
