#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
 * Assignment 2: Process Synchronization with wait() and waitpid()
 * Objective: Master synchronization by waiting for child processes and retrieving their exit statuses.
 * Approach: Use wait() for the first child and waitpid() for the second to explore different synchronization strategies.
 * Author: Gevorg
 * Date: September 24, 2025
 */

int main() {
    // Declaring PIDs and status variables to track child processes and their exit states
    pid_t firstChildPid, secondChildPid;
    int firstStatus, secondStatus;

    // Step 1: Creating the first child process
    firstChildPid = fork();
    if (firstChildPid == 0) {
        // Child 1 execution context - simple exit to test basic wait()
        printf("First child process (PID %d) is running and will exit cleanly.\n", getpid());
        exit(0); // Normal termination with success status
    } else if (firstChildPid > 0) {
        // Parent context - wait for any child to complete first
        printf("Parent (PID %d) launched first child (PID %d) and will synchronize.\n", 
               getpid(), firstChildPid);
        if (wait(&firstStatus) == -1) {
            perror("Error waiting for first child");
            exit(1);
        }
        // Verifying normal exit and extract status
        if (WIFEXITED(firstStatus)) {
            printf("Parent: First child (PID %d) finished with status %d.\n", 
                   firstChildPid, WEXITSTATUS(firstStatus));
        } else {
            printf("Parent: First child (PID %d) did not exit normally.\n", firstChildPid);
        }
    } else {
        // Handling fork failure with detailed feedback
        perror("Failed to create first child process");
        exit(1);
    }

    // Step 2: Creating the second child process with a delay to test specific waiting
    secondChildPid = fork();
    if (secondChildPid == 0) {
        // Child 2 execution context - simulate work with a delay
        printf("Second child process (PID %d) is working and will exit with custom status.\n", getpid());
        sleep(2); // Mimic a task to observe waitpid() timing
        exit(42); // Custom exit code to test status retrieval
    } else if (secondChildPid > 0) {
        // Parent context - wait specifically for the second child
        printf("Parent (PID %d) launched second child (PID %d) and will wait precisely.\n", 
               getpid(), secondChildPid);
        if (waitpid(secondChildPid, &secondStatus, 0) == -1) {
            perror("Error waiting for second child");
            exit(1);
        }
        // Analyzing the second child's exit status
        if (WIFEXITED(secondStatus)) {
            printf("Parent: Second child (PID %d) finished with status %d.\n", 
                   secondChildPid, WEXITSTATUS(secondStatus));
        } else {
            printf("Parent: Second child (PID %d) did not exit normally.\n", secondChildPid);
        }
    } else {
        perror("Failed to create second child process");
        exit(1);
    }

    // Parent confirms completion after managing all children
    printf("Parent process (PID %d) has successfully coordinated all children.\n", getpid());
    return 0; // Normal program termination
}
