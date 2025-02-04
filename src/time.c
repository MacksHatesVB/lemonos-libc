#include <stdint.h>
#include <time.h>
#include <sys/syscall.h>

time_t time(time_t t) {
	return syscall(SYSCALL_TIME, t);
}
