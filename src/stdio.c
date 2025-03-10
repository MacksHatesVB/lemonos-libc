#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

// todo: impliment
int mkdir(char * path, unsigned int mode) {
	return -1;
}

// todo: impliemnt
int rmdir(char * path) {
	return -1;
}

int mode_to_flags(char * mode) {
	int size = strlen(mode);
	if (size < 1) {
		return 0;
	}
	int flags = 0;
	switch (*mode++) {
		case 'r': flags = O_RDONLY; break;
		case 'w': flags = O_WRONLY | O_CREAT | O_TRUNC; break;
		case 'a': flags = O_WRONLY | O_CREAT | O_APPEND; break;
	}
	if (size < 2) {
		return flags;
	}
	if (*mode == '+') {
		flags ^= 0b11;
	}
	return flags;
}

FILE * fopen(char * pathname, char * mode) {
	FILE * fp = malloc(sizeof(FILE));
	fp->fd = open(pathname, mode_to_flags(mode));
	fp->offset = 0;
	return fp; // todo: impliment
}

size_t fread(void * ptr, size_t size, size_t nmemb, FILE * fp) {
	return read(fp->fd, ptr, size * nmemb);
}

size_t fwrite(void * ptr, size_t size, size_t nmemb, FILE * fp) {
	return write(fp->fd, ptr, size * nmemb);
}

long ftell(FILE * fp) {
	return fp->offset;
}

int fseek(FILE * fp, long offset, int whence) {
	fp->offset = lseek(fp->fd, offset, whence);
	return 0;
}

int fclose(FILE * fp) {
	close(fp->fd);
	free(fp);
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
	int l2 = 0;
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
			if (c == '\0') {
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
				case u'm':
					ull = (uint64_t) va_arg(*argv, unsigned long);
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ull *= ul;
					ulldtoa(ull, buffer, 10);
					puts(buffer);
					break;
				case u'p':
					l = (int) va_arg(*argv, int);
					str = (char *) va_arg(*argv, char *);
					l -= strlen(str);
					while (l-- > 0) { putchar(' '); }
					if (!str) {
						break;
					}
					puts(str);
					break;
				case u'P':
					l = (int) va_arg(*argv, int);
					ull = (uint64_t) va_arg(*argv, unsigned long);
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ull *= ul;
					ulldtoa(ull, buffer, 10);
					l -= strlen(buffer);
					while (l-- > 0) { putchar(' '); }
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
