#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pipefd[2];
	int ret;
	char buffer[13];

	// 0 : read end, 1 : write end
	pipe(pipefd);

	if(fork() > 0) {
		printf("I am Parent.\n");
		dprintf(pipefd[1], "Hello World!");
		wait(NULL);
	} else {
		sleep(1); // wait for parent to finish writing into the pipe
		printf("I am Child.\n");
		read(pipefd[0], buffer, sizeof(buffer));
		printf("Message received by child is : %s\n", buffer);
	}

	return 0;
}

