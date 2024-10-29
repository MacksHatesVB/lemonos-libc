#include <sys/syscall.h>
#include <stdlib.h>

int sched_yield() {
	syscall(SYSCALL_SCHED_YIELD);
	return 0;
}
