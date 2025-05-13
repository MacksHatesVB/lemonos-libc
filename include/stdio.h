#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

typedef struct {
	int fd;
	size_t offset;
} FILE;

typedef void (* vaprintf_puts_t)(char * string, FILE * fp, void * pass);
typedef void (* vaprintf_putc_t)(char c, FILE * fp, void * pass);

enum {
	SEEK_SET,
	SEEK_CUR,
	SEEK_END,
};

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

FILE * fopen(char * pathname, char * mode);
size_t fread(void * ptr, size_t size, size_t nmemb, FILE * fp);
size_t fwrite(void * ptr, size_t size, size_t nmemb, FILE * fp);
int sprintf(char * output, char * fmt, ...);
void fprintf(FILE * fp, char * fmt, ...);
int vfprintf(FILE * fp, char * fmt, va_list ap);
long ftell(FILE * fp);
int fseek(FILE * fp, long offset, int whence);
int fclose(FILE * fp);
void puts(char * text);
void putchar(char chr);
void printf(char * fmt, ...);
void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, long val);
void outd(uint16_t port, uint32_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
long inl(uint16_t port);
uint32_t ind(uint16_t port);
void __stdio_init();
