#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void signalHandler(int sigNum) 
{
	if (sigNum == SIGINT)
		printf("\nI don't think so\n");
}

int main (void) 
{
	int i;
	__sighandler_t ret;
	ret = signal(SIGINT, signalHandler); 
  
	if (ret == SIG_ERR) {
		fprintf(stderr,"Oops--SIGINT cannot be caught\n");
		exit(1);
	}
  
	i = 1;
	while (i < 80) {
		sleep(1);
		fprintf(stdout,"%s","P2");
		fflush(stdout); 
		i++;
	}
}
