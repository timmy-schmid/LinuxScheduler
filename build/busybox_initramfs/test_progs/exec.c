#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

int main() {
	char *args[] = { "/bin/echo", "Msg for Echo!",NULL };
	execv("/bin/echo", args);
	puts("Msg After Echo!");

}
