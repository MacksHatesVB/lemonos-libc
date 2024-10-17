#include <stdint.h>
#include <stdarg.h>

void ipc(uint64_t pid, int cmd, void * data) {
	
}

int syscall(const int number, ...) {
	va_list listp;
	va_list * argv;
	va_start(listp, number);
	argv = &listp;
	volatile register uint32_t ret asm("eax");
	uint32_t ebx = (uint32_t) va_arg(*argv, unsigned long);
	uint32_t ecx = (uint32_t) va_arg(*argv, unsigned long);
	uint32_t edx = (uint32_t) va_arg(*argv, unsigned long);
	uint32_t esi = (uint32_t) va_arg(*argv, unsigned long);
	uint32_t edi = (uint32_t) va_arg(*argv, unsigned long);
	uint32_t ebp = (uint32_t) va_arg(*argv, unsigned long);
	asm volatile ("call 0x600" : "=a"(ret) : "a" (number), "b" (ebx), "c" (ecx), "d" (edx), "S" (esi), "D"(edi));
	return ret;
}
