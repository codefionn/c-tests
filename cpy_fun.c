/**
 * What should I say ?
 * Copy (I really mean copy!) a function and execute it.
 *
 * x86_64
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>

int add(int a, int b) {
	return a + b;
}

int main(void) {
	size_t diff = ((size_t) main - (size_t) add);
	printf("page: %u, diff: %zu\n", getpagesize(), diff);

	const size_t cpyed_len = getpagesize();
	void * cpyed = memalign(getpagesize(), getpagesize());
	if (!cpyed) {
		fputs("Failed allocated alligned buffer", stderr);
		return EXIT_FAILURE;
	}

	if (mprotect((void*)cpyed, cpyed_len, PROT_READ|PROT_WRITE|PROT_EXEC) == -1) {
		perror("mprotect");
		return EXIT_FAILURE;
	}
	memcpy((void*) cpyed, (void*) add, diff);

	printf("2 + 3. Original %d, Copied: %d\n", add(2,3),
		((int (*)(int,int)) cpyed)(2,3));

	free(cpyed);
	return EXIT_SUCCESS;
}
