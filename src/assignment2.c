#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	pid_t pid1, pid2;
	int status;

	pid1 = fork();
	if(pid1 == 0){
		printf("1-st Child process PID -> %d\n", getpid());
		exit(0);
	} else if(pid1 > 0){
		wait(&status);
		printf("Parent: 1-st Child (PID %d) completed with status %d\n", pid1, WEXITSTATUS(status));
	} else{
		perror("The 1-st fork failed!");
		exit(1);
	}
	
	pid2 = fork();
	if(pid2 == 0){
		printf("2-nd Child process PID -> %d\n", getpid());
		sleep(2);
		exit(42);
	} else if(pid2 > 0){
		waitpid(pid2, &status, 0);
		printf("Parent: 2-nd Child (PID %d) completed with status %d\n", pid2, WEXITSTATUS(status));
	} else{ 
		perror("2-nd fork failed!");
		exit(1);
	}

	printf("Parent process PID is %d completed\n", getpid());
    	
	return 0;

}
