#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	pid_t pid1, pid2, pid3;

	pid1 = fork();	//first child process 
	
	//use if to fork only in the parent process
	if(pid1 != 0) {		
		printf("Parent PID: %d\n1st child PID: %d\n", getpid(), pid1);
		pid2 = fork();
		
		if (pid2 != 0){
			printf("2nd child PID: %d\n", pid2);
			pid3 = fork();

			if (pid3 != 0) {
				printf("3rd child PID: %d\n", pid3);
			}
		}
	}

	return 0;
}
