#include <stdint.h>
#include <lctl.h>
#include <time.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/syscall.h>

int gettimeofday(struct timeval * tv, void * tz) {
	return syscall(SYSCALL_GETTIMEOFDAY, tv, NULL);
}

uint64_t get_timer_timestamp() {
	return *((uint64_t *) lctl(LCTL_TIMER_TIMESTAMP));
}

time_t time(time_t t) {
	return syscall(SYSCALL_TIME, t);
}
