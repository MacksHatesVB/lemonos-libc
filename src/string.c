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

void lldtoustr(int64_t val, uint16_t * buf, int base) {
        static uint16_t rbuf[64];
        uint16_t * ptr = rbuf;
        int neg = 0;
        if (val < 0) {
                neg = 1;
                val = -val;
        }
        if (val == 0) {
                *ptr++ = '0';
        }
        while (val) {
                int digit = (uint64_t)((uint64_t) val % (long) base);
                *ptr++ = digit < 10 ? (digit + '0') : (digit - 10 + 'a');
                val /= base;
        }
        if (neg) {
                *ptr++ = '-';
        }
        ptr--;
        while (ptr >= rbuf) {
                *buf++ = *ptr--;
        }
        *buf = 0;
}

void lldtoa(int64_t val, char * buf, int base) {
        static char rbuf[64];
        char * ptr = rbuf;
        int neg = 0;
        if (val < 0) {
                neg = 1;
                val = -val;
        }
        if (val == 0) {
                *ptr++ = '0';
        }
        while (val) {
                int digit = (uint64_t)((uint64_t) val % (long) base);
                *ptr++ = digit < 10 ? (digit + '0') : (digit - 10 + 'a');
                val /= base;
        }
        if (neg) {
                *ptr++ = '-';
        }
        ptr--;
        while (ptr >= rbuf) {
                *buf++ = *ptr--;
        }
        *buf = 0;
}

/**
 *  stm32tpl --  STM32 C++ Template Peripheral Library
 *  Visit https://github.com/antongus/stm32tpl for new versions
 *
 *  Copyright (c) 2011-2020 Anton B. Gusev aka AHTOXA
 *
 *  file: ftoa.c
 *  functions: ftoa, ftoustr
 */

double rounders[] = {
	0.5,
	0.05,
	0.005,
	0.0005,
	0.00005,
	0.000005,
	0.0000005,
	0.00000005,
	0.000000005,
	0.0000000005,
	0.00000000005
};

char * ftoa(double f, char * buf, int precision) {
	char * ptr = buf;
	char * p = ptr;
	char * p1;
	char c;
	long intPart;

	if (precision > 10) {
		precision = 10;
	}

	if (f < 0) {
		f = -f;
		*ptr++ = '-';
	}

	if (precision < 0) {
		*buf = 0;
		return buf;
	}
	if (precision) {
		f += rounders[precision];
	}
	intPart = f;
	f -= intPart;
	if (!intPart) {
		*ptr++ = '0';
	} else {
		p = ptr;
		while (intPart) {
			*p++ = '0' + intPart % 10;
			intPart /= 10;
		}
		p1 = p;
		while (p > ptr) {
			c = *--p;
			*p = *ptr;
			*ptr++ = c;
		}
		ptr = p1;
	}
	if (precision) {
		*ptr++ = '.';
		while (precision--) {
			f *= 10.0;
			c = f;
			*ptr++ = '0' + c;
			f -= c;
		}
	}
	*ptr = 0;
        ptr--;
        while (*ptr == '0') {
                *ptr = '\0';
                ptr--;
        }
        if (*ptr == '.') {
                *++ptr = '0';
        }
	return buf;
}

int strlen(const char * string) {
	int i = 0;
	while (*string++) {
		i++;
	}
	return i;
}

int ustrlen(const uint16_t * string) {
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
