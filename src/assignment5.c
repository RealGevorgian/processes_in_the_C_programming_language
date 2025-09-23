#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void show_zombie(){
	
	pid_t pid = fork();
	
	if (pid == 0) {
		printf("(PID %d) Child created, and is now active\n", getpid());
		exit(0);
	} else if (pid > 0) {
		printf("(PID %d) Parent created child (PID %d)\n", getpid(), pid);
		sleep(15); // During this time we can see the zombie with htop,top, or ps
	} else {
	        perror("fork failed!");
       		exit(1);
	}
}	

void deny_zombie() {
   	
	pid_t pid = fork();
    	int status;
    
    	if (pid == 0) {
        	printf("(PID %d) Child created, and is active\n", getpid());
        	exit(0);
    	} else if (pid > 0) {
        	printf("(PID %d) Parent created Child (PID %d) and will wait\n", getpid(), pid);
        	wait(&status);
        	printf("Parent (PID %d) reaped Child (PID %d) with status %d\n", getpid(), pid, WEXITSTATUS(status));
    	} else {
        	perror("Fork failed");
        	exit(1);
    	}
}

int main() {
    	
	printf("Starting the illustration -> PID: %d\n", getpid());

    	printf("1-st version of the solution: Creating the zombie process.........\n");
    	show_zombie();

    	printf("2-nd version of the solution: Trying to deny the zombie process..........\n");
    	deny_zombie();

    	printf("(PID %d) Parent completed all illustrations\n", getpid());
    
    	return 0;

}


