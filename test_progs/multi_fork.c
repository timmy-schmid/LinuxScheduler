#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#define NPROC (20)
#define SLEEPTIME (10)

int main() {
	pid_t pids[NPROC];

	for (int i = 1; i <= NPROC; ++i) {
		pid_t pid = fork();
		pids[i - 1] = pid;

		if (pid < 0) {
			perror("Fork failed");
			return -1;
		} else if (pid == 0) {
			printf("Child %d: Started\n", getpid());
			sleep(SLEEPTIME);
			printf("Child %d: Exiting\n", getpid());
			exit(0);
		} else {
			printf("Parent: Forked %d times\n", i);
		}
	}

	for (int i = 0; i < NPROC; ++i) {
		pid_t pid = pids[i];

		if (pid > 0) {
			printf("Parent: Waiting for pid %d\n", pid);
			waitpid(pid, NULL, 0);
		}
	}

	printf("Parent: Exiting\n");

	return 0;
}
