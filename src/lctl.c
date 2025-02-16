#include <sys/syscall.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <runtime.h>
#include <lctl.h>

// this is kinda stupid but :shrug:
uint64_t timestamp = 0;

uint32_t lctl(int number, ...) {
	va_list listp;
	va_list * argv;
	va_start(listp, number);
	argv = &listp;
	uint32_t ecx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t edx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t esi = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t edi = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t ebp = (uint32_t) va_arg(*argv, uint32_t);

	switch (number) {
		case LCTL_TIMER_TIMESTAMP:
			struct timeval tv;
			gettimeofday(&tv, NULL);
			timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
			return timestamp;
	}

	if (!__is_lemonos) {
		return -1;
	}

	return (uint32_t) syscall(SYSCALL_LCTL, number, ecx, edx, esi, edi, ebp);
}
