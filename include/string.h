#pragma once

#include <stdint.h>
#include <stddef.h>

void ulldtoustr(uint64_t val, uint16_t * buf, int base);
void ulldtoa(uint64_t val, char * buf, int base);
void lldtoustr(int64_t val, uint16_t * buf, int base);
void lldtoa(int64_t val, char * buf, int base);
char * ftoa(double f, char * buf, int precision);
int strlen(const char * string);
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
