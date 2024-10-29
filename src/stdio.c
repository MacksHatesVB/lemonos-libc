#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>

void puts(char * text) {
	syscall(SYSCALL_WRITE, 1, text, strlen(text));
}
