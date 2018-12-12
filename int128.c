#include <stdio.h>
#include <stdint.h>

void print128(__int128 num) {
	if (!num)
		return;

	print128(num / 10);
	putchar(num % 10 + '0');
}

int main(void) {
	printf("UINT64_MAX: %lu\n", UINT64_MAX);

	unsigned __int128 num = UINT64_MAX;
	printf("UINT64_MAX * 2: ");
	print128(num * 2);
	putchar('\n');
	printf("UINT64_MAX + 1: ");
	print128(num + 1);
	putchar('\n');

	return 0;
}
