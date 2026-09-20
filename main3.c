#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_CHILDREN 2
#define MAX_ITERATIONS 30
#define MAX_SLEEP_SECONDS 10

/*
 * Each child runs for a random number of iterations (1-30).
 * During each iteration it sleeps for a random number of
 * seconds (1-10), then reports its PID and its parent's PID.
 */
static void run_child(void) {
    pid_t pid = getpid();

    /* Give each child a different random-number sequence. */
    srandom((unsigned int)time(NULL) ^ (unsigned int)pid);

    int iterations = (int)(random() % MAX_ITERATIONS) + 1;

    for (int i = 0; i < iterations; i++) {
        int sleep_time = (int)(random() % MAX_SLEEP_SECONDS) + 1;

        printf("Child Pid: %d is going to sleep!\n", pid);
        fflush(stdout);

        sleep((unsigned int)sleep_time);

        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",
               getpid(), getppid());
        fflush(stdout);
    }

    exit(0);
}

int main(void) {
    /*
     * Only the original parent continues this loop.
     * A newly-created child immediately enters run_child()
     * and exits when its work is complete.
     */
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");

            /* Wait for any children that were already created. */
            for (int j = 0; j < i; j++) {
                wait(NULL);
            }

            return EXIT_FAILURE;
        }

        if (pid == 0) {
            run_child();
        }
    }

    /* The parent waits for both children to terminate. */
    for (int i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t finished_pid = wait(&status);

        if (finished_pid == -1) {
            perror("wait");
            return EXIT_FAILURE;
        }

        printf("Child Pid: %d has completed\n", finished_pid);
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}
