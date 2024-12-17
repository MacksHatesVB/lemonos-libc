#include <unistd.h>
#include <runtime.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

int cpu_get_temp() {
	if (!__is_lemonos) {
		return 0;
	}
	return syscall(SYSCALL_GETTHERM);
}

void * malloc(uint32_t size) {
	return (void *) (uint32_t) syscall(SYSCALL_MALLOC, size);
}

void free(void * p) {
	syscall(SYSCALL_FREE, p);
}

int syscall(const int number, ...) {
	va_list listp;
	va_list * argv;
	va_start(listp, number);
	argv = &listp;
	uint32_t ret = 0;
	uint32_t ebx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t ecx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t edx = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t esi = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t edi = (uint32_t) va_arg(*argv, uint32_t);
	uint32_t ebp = (uint32_t) va_arg(*argv, uint32_t);
	asm volatile ("int $0x80" : "=a" (ret) : "a" (number), "b" (ebx), "c" (ecx), "d" (edx), "S" (esi), "D" (edi));
	return ret;
}
