#define _GNU_SOURCE
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int fd, x, y;

int do_something()
{
	x = 7;
	printf ("\nThis is process(thread) %d. \n", getpid());
	printf("x + y = %d\n", x + y);
	_exit(0);
}

int main(int argc, char *argv[])
{
        const int STACK_SIZE = 65536;
        char *stack, *stackTop, tempch;
        int cret;
	x = 0;
	y = 1;

        stack = malloc(STACK_SIZE);
        if (stack == NULL) {
                perror("malloc");
                exit(1);
        }
        stackTop = stack + STACK_SIZE;
         pid_t pid, ppid;

       	pid  = getpid();

	printf ("\nThis is process(thread) %d.\n", pid);
        printf("x + y = %d\n", x + y);

	cret = clone(do_something, stackTop, CLONE_VM|CLONE_FILES, NULL);
	if (cret == -1)	{
		perror("clone");
		exit(0);
	}

	return 0;
}
