#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
   int pid, fpid, ppid;

   fpid = fork ();
   pid  = getpid();
   ppid = getppid();

   printf ("fpid is is %d\n", fpid);
   sleep(5);

   if (fpid > 0) {
       printf("\nThis is Parent. My pid %d. My parent's pid %d\n", pid, ppid);
   }
   else if (fpid == 0) {
       sleep(1);
       printf("\nThis is Child. My pid %d. My parent's pid %d\n", pid, ppid);
   }
   else {
	   printf ("fork failed\n");
   }

   return (0);
}
