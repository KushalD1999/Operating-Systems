#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (void) 
{
   int pid, fpid, ppid;
   
   fpid = fork ();
   
   printf ("fpid is is %d\n", fpid);
   sleep(5);
   
   if (fpid > 0) {
       pid  = getpid();
       ppid = getppid();
       printf ("\nThis is Parent. My pid %d. My parent's pid %d\n", pid, ppid);
   }
   else if (fpid == 0) {
       sleep(1);
       pid  = getpid();
       ppid = getppid();
       printf ("\nThis is Child. My pid %d. My parent's pid %d\n", pid, ppid);
   }
   else {
       printf ("fork failed\n");
   }
   
   return (0);
}
