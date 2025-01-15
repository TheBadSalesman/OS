#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


//signal handler for SIGINT, catches it and does nothing
void sigint_handler(int sig) {
	printf("SIGINT caught by child process, parent must terminate :O\n");
}


int main() {
	pid_t pid = fork();

	if(pid < 0) {
		perror("Forking error!");
		return 1;
	} 
	else if(pid == 0) {	//child process

		//Register signal handler for SIGINT
		if(signal(SIGINT, sigint_handler) == SIG_ERR) {
			perror("Error when registering handler.");
			return 1;
		}

		printf("Child process (PID: %d) waiting to be stopped...\n", getpid());
		
		//await termination signal from parent process
		while(1) {
			pause();
		}
	}
	else {	//Parent process

		printf("Parent process PID: %d, child process PID: %d\n", getpid(), pid);

		sleep(2);	//wait for child process to enter pause mode

		printf("Parent sending SIGINT to child.\n");
		if(kill(pid, SIGINT) == -1) {
			perror("SIGINT sending error");
			return 1;
		}

		sleep(2);	//wait for child process to catch last signal

		printf("Left with no choice, parent must terminate :(\n");
		if(kill(pid, SIGTERM) == -1) {
			perror("Termination error");
			return -1;
		}

		wait(NULL);
		printf("Child terminated.\n");
	}

	return 0;
}
