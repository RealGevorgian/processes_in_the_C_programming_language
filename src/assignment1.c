#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* 
 * Assignment 1: Basic Process Creation with fork()
 * Purpose: Explore how fork() creates a child process and how PIDs are assigned.
 * Author: Gevorg
 * Date: September 24, 2025
 */

int main() {
    // Declare pid_t to store the result of fork(), which will be the child’s PID or an error code
    pid_t childProcessId = fork();

    // Check the return value to determine the process context
    if (childProcessId == 0) {
        // This block runs in the child process
        printf("Child process launched! My PID is %d. Time to exit.\n", getpid());
        exit(0); // Exit cleanly to free resources
    } else if (childProcessId > 0) {
        // This block runs in the parent process
        printf("Parent process here! My PID is %d, and I created child PID %d.\n", 
               getpid(), childProcessId);
        // No wait() here, as per assignment, letting the child run independently
    } else {
        perror("Oops! Failed to create a child process");
        exit(1); // Exit with error status
    }

    return 0; // Normal exit for parent, though unreachable after fork failure path
}
