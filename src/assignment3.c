#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Assignment 3: Exploring atexit() for Process Cleanup
 * Objective: Understand and demonstrate the atexit() function for registering cleanup actions.
 * Approach: Register two cleanup functions, test termination at different points, and observe LIFO order.
 * Author: Gevorg
 * Date: September 24, 2025
 */

void cleanupFirst() {
    // First cleanup function - simulates releasing a critical resource
    printf("Cleanup #1 activated: Releasing memory allocation for PID %d.\n", getpid());
}

void cleanupSecond() {
    // Second cleanup function - simulates closing a file or connection
    printf("Cleanup #2 activated: Closing network connection for PID %d.\n", getpid());
}

int main() {
    printf("Program startup - My PID is %d. Let’s set up cleanup!\n", getpid());

    // Register cleanup functions - note the LIFO execution order (last registered, first executed)
    printf("Attempting to register first cleanup function...\n");
    if (atexit(cleanupSecond) != 0) { // Register second cleanup first for LIFO test
        perror("Registration of second cleanup failed");
        return 1;
    }
    printf("First cleanup registered successfully.\n");

    printf("Attempting to register second cleanup function...\n");
    if (atexit(cleanupFirst) != 0) { // Register first cleanup last
        perror("Registration of first cleanup failed");
        return 1;
    }
    printf("Second cleanup registered successfully.\n");

    printf("All cleanup functions are set. Testing first exit point...\n");
    exit(0); // First termination point - triggers cleanup in reverse order

    // Uncomment the next block to test a later exit point
    /*
    printf("Moving past first exit - testing second exit point...\n");
    sleep(1); // Simulate some work
    exit(42); // Second termination point with a custom status
    */

    printf("This won’t print - after all exit points.\n"); // Unreachable code
    return 0; // Normal termination (also unreachable due to exit())
}
