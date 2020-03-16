#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/*
Purpose: Use 2 threads to increment myglobal exactly 40 times in total.
Compile: using -pthread option
 */

/*
 2. When the thread is run, variable j is set the global variable and is incremented by 1.
    In the main function myglobal is incremented by 1 and then again set to variable j. Since the
    thread does not increment myglobal before myglobal is set to myglobal = myglobal + 1, the operation is overwritten.

 3. It will be 40 in the case when main function adds 1 to myglobal, then the thread
    function does j = j + 1 and myglobal = j before the main does myglobal = myglobal + 1.
*/


sem_t semaphoreVar;
int myglobal = 0;

 void *thread_function(void *arg)
 {
    sem_wait(&semaphoreVar);
	int i,j;

	for (i = 0; i < 20; i++)
	{
		j = myglobal;
		j = j + 1;
		printf(".");
		fflush(stdout);
		sleep(0.2);
		myglobal = j;
	}
	sem_post(&semaphoreVar);
	return NULL;
}

int main(void)
{
	pthread_t mythread;
	int i;
	sem_init(&semaphoreVar, 0, 1);

	if (pthread_create(&mythread, NULL, thread_function, NULL)) {
		printf("error creating thread.");
		abort();
	}

	sem_wait(&semaphoreVar);

	for (i = 0; i < 20; i++)
	{
		myglobal = myglobal + 1;
		printf("o");
		fflush(stdout);
		sleep(0.21);
	}

    sem_post(&semaphoreVar);

	if (pthread_join(mythread, NULL)) {
		printf("error joining thread.");
		abort();
	}

	printf("\nmyglobal equals %d\n", myglobal);
    sem_destroy(&semaphoreVar);

	exit(0);
}
