#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int printChar;

	if (argc != 2) {
		fprintf(stderr, "usage: %s character\n", argv[0]);
		exit(1);
	}

	printChar = argv[1][0];
	int i = 1;

	while (i < 80) {
		sleep(1);
		fprintf(stdout,"%c",printChar);
		fflush(stdout);
		i++;
	}

	return 0;
}
