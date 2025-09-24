#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
 * Assignment 5: Mastering Zombie Process Management
 * Objective: Illustrate zombie process creation and prevention using wait().
 * Approach: Implement two versions—one to create a zombie with a long sleep for observation,
 *           and another to prevent it with wait(), followed by an explanation of the mechanism.
 * Author: Gevorg
 * Date: September 24, 2025, 10:00 PM +04
 */

void createZombieProcess() {
    // Function to demonstrate zombie process creation
    pid_t childPid = fork();
    if (childPid == 0) {
        // Child process context - exits immediately to become a zombie
        printf("Child Process (PID %d) has started and will exit now.\n", getpid());
        exit(0); // Normal exit triggers zombie state if not reaped
    } else if (childPid > 0) {
        printf("Parent Process (PID %d) spawned Child (PID %d) without reaping.\n", getpid(), childPid);
        printf("Observation Tip: Run 'ps aux | grep Z' or check 'htop' (enable Z state) now for ~15 seconds.\n");
        sleep(15); // Extended pause to allow manual zombie observation
    } else {
        fprintf(stderr, "Parent (PID %d) failed to fork child: ", getpid());
        perror(NULL);
        exit(1);
    }
}

void preventZombieProcess() {
    // Function to demonstrate zombie prevention with wait()
    pid_t childPid = fork();
    int exitStatus;
    if (childPid == 0) {
        // Child process context - exits to test wait() reaping
        printf("Child Process (PID %d) is active and will terminate.\n", getpid());
        exit(0); // Normal exit, reaped by parent
    } else if (childPid > 0) {
        printf("Parent Process (PID %d) spawned Child (PID %d) and will reap it.\n", getpid(), childPid);
        if (wait(&exitStatus) == -1) {
            fprintf(stderr, "Parent (PID %d) failed to wait for Child (PID %d): ", getpid(), childPid);
            perror(NULL);
            exit(1);
        }
        // Verifing and reporting the child's exit status
        if (WIFEXITED(exitStatus)) {
            printf("Parent (PID %d) successfully reaped Child (PID %d) with status %d.\n", 
                   getpid(), childPid, WEXITSTATUS(exitStatus));
        } else {
            printf("Parent (PID %d): Child (PID %d) did not exit normally.\n", getpid(), childPid);
        }
    } else {
        fprintf(stderr, "Parent (PID %d) failed to fork child: ", getpid());
        perror(NULL);
        exit(1);
    }
}

int main() {
    printf("Launching Zombie Process Demonstration - Parent PID: %d\n", getpid());

    printf("Step 1: Executing version to create a zombie process...\n");
    createZombieProcess();

    printf("Step 2: Executing version to prevent a zombie process...\n");
    preventZombieProcess();

    printf("Parent Process (PID %d) has completed the demonstration.\n", getpid());
    return 0; // Normal program termination
}
