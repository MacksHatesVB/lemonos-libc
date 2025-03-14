#pragma once

#include <stdint.h>
#include <stddef.h>

char * step_line(char * line);
int line_strlen(char * line);
int char_search(char chr, char * hay);

int isdigit(int c);
int isblank(int c);
int isspace(int c);
void ulldtoustr(uint64_t val, uint16_t * buf, int base);
void ulldtoa(uint64_t val, char * buf, int base);
void lldtoustr(int64_t val, uint16_t * buf, int base);
void lldtoa(int64_t val, char * buf, int base);
long strtol(const char* str);
int atoi(char * string);
char * ftoa(double f, char * buf, int precision);
float atof(char * s);

char * ustrtoa(uint16_t * unicode, char * ascii);
long ustrtol(const uint16_t * str);
uint16_t * ustrnexti(uint16_t * string);

int strcmp(char * x, char * y);
int strlen(const char * string);
uint16_t * ustrcpy(uint16_t * dest, uint16_t * src);
char * strcpy(char * dest, char * src);
int memcmp(void * x, void * y, size_t length);
char * strdup(char * string);
int ustrlen(const uint16_t * string);
void * memset(void * dest, int val, size_t length);
void * memcpy(void * dest, const void * src, size_t length);

// todo: not this
static inline uint32_t * memset32(uint32_t * dest, uint32_t val, size_t length) {
	void * temp = dest;
	__asm__ volatile (
		"rep stosl"
		: "=D"(dest),"=c"(length)
		: "0"(dest),"a"(val),"1"(length)
		: "memory"
	);
	return temp;
}


static inline uint32_t * memcpy32(uint32_t * dest, uint32_t * src, size_t length) {
	int d0, d1, d2;
	asm volatile (
		"rep ; movsl\n\t"
		"testb $2,%b4\n\t"
		"je 1f\n\t"
		"movsw\n"
		"1:\ttestb $1,%b4\n\t"
		"je 2f\n\t"
		"movsb\n"
		"2:"

		: "=&c" (d0), "=&D" (d1), "=&S" (d2)
		: "0" (length), "q" (length*4),"1" ((long) dest),"2" ((long) src)
		: "memory"
	);
	return dest;
}
