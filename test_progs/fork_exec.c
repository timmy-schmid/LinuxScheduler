#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

int main() {
	pid_t pid = fork();

	if (pid < 0) {
		perror("Fork failed");
		return -1;
	} else if (pid == 0) {
		char *args[] = { "/bin/echo", "Hello from the child!" };
		execv("/bin/echo", args);
	} else {
		puts("Hello from the parent!");
	}

	waitpid(pid, NULL, 0);
}
