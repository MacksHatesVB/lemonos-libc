#include <stdint.h>
#include <time.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/syscall.h>

int gettimeofday(struct timeval * tv, void * tz) {
	return syscall(SYSCALL_GETTIMEOFDAY, tv, NULL);
}

time_t time(time_t t) {
	return syscall(SYSCALL_TIME, t);
}
