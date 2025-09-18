#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid = fork();

	if(pid == 0){
		printf("PID of the Child` %d\n", getpid());
		exit(0);
	}

	else if(pid > 0){
		printf("PID of the Parent` %d\n", getpid());
	}

	else{
		perror("fork failed");
		exit(1);
	}

	return 0;
}
