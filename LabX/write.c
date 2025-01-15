#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>

int main() {
	FILE *fp = fopen("write.txt", "w");
        if(fp == NULL) {
        	perror("Error openning file");
                return 1;
        }


	pid_t pid = fork();

	if (pid < 0) {
		perror("Fork error");
		return 1;
	} else if (pid == 0) {
		fprintf(fp, "Child process PID: %d\n", getpid());

		if(fclose(fp) != 0) {
			perror("Error closing file");
			return 1;
		}

		exit(0);
	} else {
		wait(NULL);

                fprintf(fp, "Parent process PID: %d\n", getpid());

                if(fclose(fp) != 0) {
                        perror("Error closing file");
                        return 1;
                }

	}

	return 0;
}
