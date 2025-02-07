#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>

FILE * fopen(const char * pathname, const char * mode) {
	return NULL; // todo: impliment
}

int fclose(FILE * stream) {
	return -1; // tood: impliment
}

void puts(char * text) {
	syscall(SYSCALL_WRITE, 1, text, strlen(text));
}

void putchar(char chr) {
	syscall(SYSCALL_WRITE, 1, &chr, 1);
}

void printf(char * fmt, ...) {
	va_list listp;
	va_list * argv;

	char c;
	unsigned long ul = 0;
	uint64_t ull = 0;
	int l = 0;
	double f = 0;
	char * str;
	char buffer[128];

	va_start(listp, fmt);
	argv = &listp;
	memset(buffer, 0, 128);

	while ((c = *fmt) != '\0') {
		if (c != '%') {
			putchar(c);
			fmt++;
			continue;
		} else {
			fmt++;
			c = *fmt;
			if (c == '0') {
				break;
			}
			switch (c) {
				default:
					break;
				case u'x':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 16);
					puts(buffer);
					break;
				case u'b':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 2);
					puts("0b");
					puts(buffer);
					break;
				case u'r':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 16);
					ul = strlen(buffer);
					ul = 8 - ul;
					puts("0x");
					while (ul--) {
						puts("0");
					}
					puts(buffer);
					break;
				case u'f':
					f = (double) va_arg(*argv, double);
					ftoa(f, buffer, 10);
					puts(buffer);
					break;
				case u'd':
					l = (int32_t) va_arg(*argv, long);
					lldtoa(l, buffer, 10);
					puts(buffer);
					break;
				case u'o':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 8);
					puts(buffer);
					break;
				case u'u':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 10);
					puts(buffer);
					break;
				case u'l':
					ull = *(uint64_t *) va_arg(*argv, uint64_t *);
					ulldtoa(ull, buffer, 10);
					puts(buffer);
					break;
				case u's':
				case u'8':
					str = (char *) va_arg(*argv, char *);
					puts(str);
					break;
				case u'c':
					ul = (char) va_arg(*argv, char);
					putchar(ul);
					break;
				case u'%':
					putchar(u'%');
					break;
			}
			fmt++;
			continue;
		}
	}
	va_end(listp);
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
