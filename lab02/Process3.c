#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main (int argc, char *argv[]) 
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s PID\n", argv[0]);     
		exit(1);
	}

	kill (atol(argv[1]),SIGINT);

	return 0;    
}
