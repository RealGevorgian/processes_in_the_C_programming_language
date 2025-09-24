#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
 * Assignment 4: Managing Fork and Exit Status
 * Objective: Explore creating multiple child processes and analyzing their exit statuses.
 * Approach: Use fork() to spawn two children with distinct exit codes, waitpid() for precise synchronization,
 *           and evaluate termination types with status macros.
 * Author: Gevorg
 * Date: September 24, 2025, 09:43 PM +04
 */

int main() {
    // Declaring variables to track child PIDs and their exit statuses
    pid_t childOnePid, childTwoPid;
    int childOneStatus, childTwoStatus;

    // Phase 1: Launching the first child process
    childOnePid = fork();
    if (childOnePid == 0) {
        // Child 1 context - simulate a successful task
        printf("Child #1 (PID %d) is active and completing a successful task.\n", getpid());
        exit(0); // Exit with success status
    } else if (childOnePid > 0) {
        printf("Parent (PID %d) has spawned Child #1 with PID %d.\n", getpid(), childOnePid);
    } else {
        // Handling fork failure with detailed logging
        fprintf(stderr, "Parent (PID %d) encountered an error spawning Child #1: ", getpid());
        perror(NULL);
        exit(1);
    }

    // Phase 2: Launching the second child process
    childTwoPid = fork();
    if (childTwoPid == 0) {
        // Child 2 context - simulate an error condition
        printf("Child #2 (PID %d) is running and encountering an issue.\n", getpid());
        exit(13); // Exit with a custom error code (e.g., permission denied)
    } else if (childTwoPid > 0) {
        printf("Parent (PID %d) has spawned Child #2 with PID %d.\n", getpid(), childTwoPid);
    } else {
        fprintf(stderr, "Parent (PID %d) encountered an error spawning Child #2: ", getpid());
        perror(NULL);
        exit(1);
    }

    // Phase 3: Synchronizing with Child 1 using waitpid()
    printf("Parent (PID %d) is now waiting for Child #1 (PID %d) to finish...\n", getpid(), childOnePid);
    if (waitpid(childOnePid, &childOneStatus, 0) == -1) {
        fprintf(stderr, "Parent (PID %d) failed to wait for Child #1 (PID %d): ", getpid(), childOnePid);
        perror(NULL);
        exit(1);
    }
    // Analyzing Child 1's termination
    if (WIFEXITED(childOneStatus)) {
        printf("Parent: Child #1 (PID %d) terminated normally with status %d.\n", 
               childOnePid, WEXITSTATUS(childOneStatus));
    } else {
        printf("Parent: Child #1 (PID %d) did not terminate normally.\n", childOnePid);
    }

    // Phase 4: Synchronizing with Child 2 using waitpid()
    printf("Parent (PID %d) is now waiting for Child #2 (PID %d) to finish...\n", getpid(), childTwoPid);
    if (waitpid(childTwoPid, &childTwoStatus, 0) == -1) {
        fprintf(stderr, "Parent (PID %d) failed to wait for Child #2 (PID %d): ", getpid(), childTwoPid);
        perror(NULL);
        exit(1);
    }
    // Analyzing Child 2's termination
    if (WIFEXITED(childTwoStatus)) {
        printf("Parent: Child #2 (PID %d) terminated normally with status %d.\n", 
               childTwoPid, WEXITSTATUS(childTwoStatus));
    } else {
        printf("Parent: Child #2 (PID %d) did not terminate normally.\n", childTwoPid);
    }

    // Phase 5: Parent completes its duties
    printf("Parent (PID %d) has successfully managed all child processes.\n", getpid());
    return 0; // Normal program exit
}
