#include <stdint.h>
#include <stddef.h>

// todo: clean this shit up, accelerate with sse and avx

void ulldtoustr(uint64_t val, uint16_t * buf, int base) {
	static uint16_t rbuf[64];
	uint16_t * ptr = rbuf;
	if (val == 0) {
		*ptr++ = '0';
	}
	while (val) {
		int digit = (uint64_t)((uint64_t) val % (long) base);
		*ptr++ = digit < 10 ? (digit + '0') : (digit - 10 + 'a');
		val /= base;
	}
	ptr--;
	while (ptr >= rbuf) {
		*buf++ = *ptr--;
	}
	*buf = 0;
}

void ulldtoa(uint64_t val, char * buf, int base) {
	static char rbuf[64];
	char * ptr = rbuf;
	if (val == 0) {
		*ptr++ = '0';
	}
	while (val) {
		int digit = (uint64_t)((uint64_t) val % (long) base);
		*ptr++ = digit < 10 ? (digit + '0') : (digit - 10 + 'a');
		val /= base;
	}
	ptr--;
	while (ptr >= rbuf) {
		*buf++ = *ptr--;
	}
	*buf = 0;
}

int strlen(const char * string) {
	int i = 0;
	while (*string++) {
		i++;
	}
	return i;
}

void * memset(void * dest, int val, size_t length) {
	register uint8_t * temp = dest;
	while (length-- > 0) {
		*temp++ = val;
	}
	return dest;
}

void * memcpy(void * dest, const void * src, size_t length) {
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
		: "0" (length/4), "q" (length),"1" ((long) dest),"2" ((long) src)
		: "memory"
	);
	return dest;
}
