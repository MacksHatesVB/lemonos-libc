#include <sys/syscall.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

/*int prctl(const int op, ...) {
	va_list listp;
	va_list * argv;
	va_start(listp, op);
	argv = &listp;
	uint32_t arg1 = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t arg2 = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t arg3 = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t arg4 = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t arg5 = (uint32_t) va_arg(*argv, uint32_t);
	return syscall(SYSCALL_PRCTL, arg1, arg2, arg3, arg4, arg5);
}
*/
