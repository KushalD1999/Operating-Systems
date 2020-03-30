// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
3. When kirk ended, spock also ends since kirk is the sender and spock is the receiver. The long set within the msgnd in kirk is equivalent to the
    the long set within the msgrcv for spock. Spcok also receives messages from kirk, which means that when kirk ends, spcok will no longer be receiving any messages
    resulting in spock to end as well.

4. Spock will not execute with kirk running. If spock notices that the ID of kirk is -1 (no instance of kirk is running), it will
    exit with the following lines:
    perror("msgget");
    exit(1);

5. When starting kirk in one window and then spock in another while giving kirk orders, spock wont end. Spock is the receiver of kirk,
    so it is basically connected to kirk and will not end until kirk is done. Kirk destroys the messagequeues at the end and when the
    messages are destroyed only then kirk terminates.When kirk terminates, spock also ends. 


7. kirk.c basically deletes the message queue by using msgctl. msgctl removes the message queue from the kernel with the msqid we have been
   using as an argument. It will safely delete the message queue, unless the user inputs CTRL+C instead pf CTRL+D, in which case
   the message queue will stick around.

8. After running the above instructions, we can observe that the process scheduling of the program basically runs in a queue, and follows
    the first in first out method. It basically runs in the order of which it is ran.
*/

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    int key;
    if (scanf("%d", &key) != 1) {
        printf("Please enter an integer next time.\n");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Enter lines of text, ^D to quit:\n");

    buf.mtype = 1; /* we don't really care in this case */

    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
	{
        int len = strlen(buf.mtext);

        /* ditch newline at end, if it exists */
        if (buf.mtext[len-1] == '\n')
			buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
