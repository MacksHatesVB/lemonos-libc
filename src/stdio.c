#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

static FILE stdinfp;
static FILE stdoutfp;
static FILE stderrfp;
FILE * stdin;
FILE * stdout;
FILE * stderr;

void __stdio_init() {
	stdin = &stdinfp;
	stdout = &stdoutfp;
	stderr = &stderrfp;

	stdin->fd = 0;
	stdout->fd = 1;
	stderr->fd = 2;

	stdin->offset = 0;
	stdout->offset = 0;
	stderr->offset = 0;
}

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

int fflush(FILE * fp) {} // lol

int getchar() {
	return '\n';
}

void puts(char * text) {
	syscall(SYSCALL_WRITE, 1, text, strlen(text));
}

void putchar(char chr) {
	syscall(SYSCALL_WRITE, 1, &chr, 1);
}

void fputs(char * text, FILE * fp) {
	syscall(SYSCALL_WRITE, fp->fd, text, strlen(text));
}

void fputc(char chr, FILE * fp) {
	syscall(SYSCALL_WRITE, fp->fd, &chr, 1);
}

static int printf_prepass(char * fmt) {
	char chr = 0;
	int i = 0;
	while (chr = *fmt++) {
		if (chr == '%') {
			return -1;
		}
		i++;
	}
	return i;
}

void vaprintf(void * pass, va_list * argv, FILE * fp, vaprintf_puts_t puts, vaprintf_putc_t putc, char * fmt) {
	/*
	  # optimisation for formatless strings, printf("Hello World!\n") for example

	 pros:
	  - Formatless strings will no longer be needlessly broken up into tonnes of little write() calls
	 cons:
	  - Performance penalty if the string has formatting
	  - Strings with formatting are still broken up
	*/
	int length = printf_prepass(fmt);
	if (length != -1) { // check if the string contains a `%` character (return length or -1)
		puts(fmt, fp, pass);
		return;
	}

	char c;
	unsigned long ul = 0;
	uint64_t ull = 0;
	int l = 0;
	int l2 = 0;
	double f = 0;
	char * str;
	char buffer[128];
	memset(buffer, 0, 128);

	while ((c = *fmt) != '\0') {
		if (c != '%') {
			putc(c, fp, pass);
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
					puts(buffer, fp, pass);
					break;
				case u'b':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 2);
					puts("0b", fp, pass);
					puts(buffer, fp, pass);
					break;
				case u'r':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 16);
					ul = strlen(buffer);
					ul = 8 - ul;
					puts("0x", fp, pass);
					while (ul--) {
						puts("0", fp, pass);
					}
					puts(buffer, fp, pass);
					break;
				case u'f':
					f = (double) va_arg(*argv, double);
					ftoa(f, buffer, 10);
					puts(buffer, fp, pass);
					break;
				case u'd':
					l = (int32_t) va_arg(*argv, long);
					lldtoa(l, buffer, 10);
					puts(buffer, fp, pass);
					break;
				case u'o':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 8);
					puts(buffer, fp, pass);
					break;
				case u'u':
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ulldtoa(ul, buffer, 10);
					puts(buffer, fp, pass);
					break;
				case u'm':
					ull = (uint64_t) va_arg(*argv, unsigned long);
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ull *= ul;
					ulldtoa(ull, buffer, 10);
					puts(buffer, fp, pass);
					break;
				case u'p':
					l = (int) va_arg(*argv, int);
					str = (char *) va_arg(*argv, char *);
					l -= strlen(str);
					while (l-- > 0) { putc(' ', fp, pass); }
					if (!str) {
						break;
					}
					puts(str, fp, pass);
					break;
				case u'P':
					l = (int) va_arg(*argv, int);
					ull = (uint64_t) va_arg(*argv, unsigned long);
					ul = (uint32_t) va_arg(*argv, unsigned long);
					ull *= ul;
					ulldtoa(ull, buffer, 10);
					l -= strlen(buffer);
					while (l-- > 0) { putc(' ', fp, pass); }
					puts(buffer, fp, pass);
					break;
				case u'l':
					ull = *(uint64_t *) va_arg(*argv, uint64_t *);
					ulldtoa(ull, buffer, 10);
					puts(buffer, fp, pass);
					break;
				case u's':
				case u'8':
					str = (char *) va_arg(*argv, char *);
					puts(str, fp, pass);
					break;
				case u'c':
					ul = (char) va_arg(*argv, char);
					putc(ul, fp, pass);
					break;
				case u'%':
					putc(u'%', fp, pass);
					break;
			}
			fmt++;
			continue;
		}
	}
}

void vaprintf_stream_puts(char * string, FILE * fp, void * pass) {
	fputs(string, fp);
}

void vaprintf_stream_putc(char c, FILE * fp, void * pass) {
	fputc(c, fp);
}

void vaprintf_buffer_puts(char * string, FILE * fp, void * pass) {
	char ** output = pass;
	strcpy(*output, string);
	*output += strlen(string);
	**output = 0;
}

void vaprintf_buffer_putc(char c, FILE * fp, void * pass) {
	char ** outputp = pass;
	char * output = *outputp;
	output[0] = c;
	output[1] = 0;
	*outputp += 1;
}

int sprintf(char * output, char * fmt, ...) {
	va_list listp;
	va_list * argv;

	va_start(listp, fmt);
	argv = &listp;
	vaprintf(&output, argv, stdout, vaprintf_buffer_puts, vaprintf_buffer_putc, fmt);
	va_end(listp);
}

int vfprintf(FILE * fp, char * fmt, va_list ap) {
	va_list * argv = &ap;
	vaprintf(NULL, argv, fp, vaprintf_stream_puts, vaprintf_stream_putc, fmt);
}

void fprintf(FILE * fp, char * fmt, ...) {
	va_list listp;
	va_list * argv;

	va_start(listp, fmt);
	argv = &listp;
	vaprintf(NULL, argv, fp, vaprintf_stream_puts, vaprintf_stream_putc, fmt);
	va_end(listp);
}

void printf(char * fmt, ...) {
	va_list listp;
	va_list * argv;

	va_start(listp, fmt);
	argv = &listp;
	vaprintf(NULL, argv, stdout, vaprintf_stream_puts, vaprintf_stream_putc, fmt);
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
