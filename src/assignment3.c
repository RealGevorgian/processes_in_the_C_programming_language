#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void first_cleanup(){
	printf("1-st Cleanup function is executed A\n");
}

void second_cleanup(){
	printf("2-nd Cleanup function is executed B\n");
}

int main(){
	printf("Main programm is started -> PID: %d\n", getpid());

	printf("Registering the 1-st cleanup function...\n");
	if(atexit(first_cleanup) != 0){
		perror("failed to register the first cleanup");
		return 1;
	}

	printf("Registering the 2-nd cleanup function...\n");
    	if (atexit(second_cleanup) != 0) {
        	perror("Failed to register the second cleanup");
        	return 1;
   	}	

	printf("Both cleanup functions registered successfully\n");
   
    	printf("About to call exit(0) - cleanup functions should execute now\n");
    	exit(0);

    	printf("This should not print - after exit(0)\n");

    	return 0;
}
