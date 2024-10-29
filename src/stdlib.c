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

void outb(uint16_t port, uint8_t val) {
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

void outw(uint16_t port, uint16_t val) {
	asm volatile ("outw %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

void outl(uint16_t port, long val) {
	asm volatile ("outl %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

void outd(uint16_t port, uint32_t val) {
	asm volatile ("outl %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

long inl(uint16_t port) {
	long ret;
	asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint32_t ind(uint16_t port) {
	uint32_t ret;
	asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
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
