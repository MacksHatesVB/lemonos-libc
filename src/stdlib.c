#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

void exit(int status) {
	syscall(SYSCALL_EXIT, status);
}
