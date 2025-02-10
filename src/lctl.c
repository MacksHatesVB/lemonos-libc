#include <sys/syscall.h>
#include <stdint.h>
#include <stdarg.h>
#include <lctl.h>

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
	return (uint32_t) syscall(SYSCALL_LCTL, number, ecx, edx, esi, edi, ebp);
}
