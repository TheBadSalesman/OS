#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {

	int fd[2];	//pipe file handlers
	if(pipe(fd) == -1) {
		perror("Error when opening the pipe!\n");
		return 1;
	}

	pid_t pid = fork();

	if(pid > 0) { //parent process
		close(fd[0]);
		int x;
		printf("Input a number and press Enter:\n");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
		printf("Parent sent: %d.\n", x);
		wait(NULL);
	} else {	//child process
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Child received: %d.\n", y);
	}

	return 0;
}
