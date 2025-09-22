#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid_one, pid_two;
    int status_one, status_two;

    pid_one = fork();
    if (pid_one == 0) {
        printf("The first child (PID %d) is executing\n", getpid());
        exit(0);
    } else if (pid_one > 0) {
        printf("Parent (PID %d) created the first Child (PID %d)\n", getpid(), pid_one);
    } else {
        perror("The first fork failed!");
        exit(1);
    }

    pid_two = fork();
    if (pid_two == 0) {
        printf("The second Child (PID %d) executing\n", getpid());
        exit(13);
    } else if (pid_two > 0) {
        printf("Parent (PID %d) created the second Child (PID %d)\n", getpid(), pid_two);
    } else {
        perror("The second fork failed!");
        exit(1);
    }

    printf("Parent waiting for Child 1 (PID %d)...\n", pid_one);
    waitpid(pid_one, &status_one, 0);

    if (WIFEXITED(status_one)) {
        printf("The first Child (PID %d) exited normally with status %d\n",
               pid_one, WEXITSTATUS(status_one));
    } else {
        printf("Child one (PID %d) did not exit normally\n", pid_one);
    }

    printf("Parent waiting for the second Child (PID %d)...\n", pid_two);
    waitpid(pid_two, &status_two, 0);

    if (WIFEXITED(status_two)) {
        printf("The second Child (PID %d) exited normally with status %d\n",
               pid_two, WEXITSTATUS(status_two));
    } else {
        printf("The second Child (PID %d) did not exit normally\n", pid_two);
    }

    printf("Parent (PID %d) completed all child processing\n", getpid());

    return 0;
}
