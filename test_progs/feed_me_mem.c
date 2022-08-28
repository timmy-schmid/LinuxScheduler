#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define ALLOC_SIZE (4096)

static size_t mem_alloced = 0;
static char *mem_ptr = NULL;

void signal_handler(int sig) {
	if (mem_ptr == NULL) {
		mem_ptr = malloc(ALLOC_SIZE);
		if (mem_ptr == NULL) {
			perror("Allocation failed, exiting...\n");
			exit(1);
		} else {
			mem_alloced = ALLOC_SIZE;
		}
	} else {
		void *new_ptr = realloc(mem_ptr, mem_alloced + ALLOC_SIZE);
		if (new_ptr == NULL) {
			perror("Allocation failed, exiting...\n");
			exit(1);
		} else {
			mem_alloced += ALLOC_SIZE;
			mem_ptr = new_ptr;
		}
	}
}

int main() {
	const struct sigaction act = {signal_handler, NULL, 0, 0, NULL};
	sigaction(SIGINT, &act, NULL);

	while (1) {
		printf("Bytes Allocated: %zu\n", mem_alloced);
		sleep(1);
	}

	return 0;
}
