#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

// todo: clean this shit up, accelerate with sse and avx
// q: ¿sse and avx acceleration done for us by gcc?

char * step_line(char * line) {
	while (*line && *line != '\n') {
		line++;
	}
	if (*line == '\n') {
		line++;
	}
	return line;
}

int line_strlen(char * line) {
	int i = 0;
	while (*line && *line != '\n') {
		i++;
		line++;
	}
	return i;
}

int char_search(char chr, char * hay) {
	while (*hay) {
		if (*hay == chr) {
			return 1;
		}
		hay++;
	}
	return 0;
}

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
		int digit = (uint64_t) ((uint64_t) val % (long) base);
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
                int digit = (uint64_t) ((uint64_t) val % (long) base);
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
                int digit = (uint64_t) ((uint64_t) val % (long) base);
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

long strtol(const char * str) {
	long acc = 0;
	int sign = 1;

	while (isspace(*str)) str++;

	if (*str == u'+') {
		str++;
	} else if (*str == u'-') {
		sign = -1;
		str++;
	}

	while (*str && isdigit(*str)) {
		acc = acc * 10 + (*str - u'0');
		str++;
	}

	return sign > 0 ? acc : -acc;
}

long ustrtol(const uint16_t * str) {
	long acc = 0;
	int sign = 1;


	while (isspace(*str)) str++;

	if (*str == u'+') {
		str++;
	} else if (*str == u'-') {
		sign = -1;
		str++;
	}

	while (*str && isdigit(*str)) {
		acc = acc * 10 + (*str - u'0');
		str++;
	}

	return sign > 0 ? acc : -acc;
}

uint64_t strtolh(const char *nptr, char **endptr, int base) {
	register const char *s = nptr;
	register uint64_t acc;
	register int c;
	register uint64_t cutoff;
	register int neg = 0, any, cutlim;
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
		c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	cutoff = neg ? -(unsigned long long int)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long long int)base;
	cutoff /= (unsigned long long int)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
		//errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *) (any ? s - 1 : nptr);
	return (acc);
}

uint32_t strtolhauto(char * string) {
        if ((string[0] == u'0') && (string[1] == u'x')) {
                return strtolh(string, 0, 16);
        } else if ((string[0] == u'0') && (string[1] == u'b')) {
                return strtolh(string + 2, 0, 2);
        } else if (string[0] == u'#') {
                return strtolh(string + 1, 0, 16);
        } else if ((string[0] == u'0') && (string[1] == u'o')) {
                return strtolh(string + 2, 0, 8);
        } else if (string[strlen(string) - 1] == u'h') {
                return strtolh(string, 0, 16);
        } else {
                return strtolh(string, 0, 10);
        }
}

int atoi(char * string) {
	return strtol(string);
}

uint16_t * ustrnexti(uint16_t * string) {
	while (isdigit(*string)) {
		string++;
	}
	return string;
}

char * ustrtoa(uint16_t * unicode, char * ascii) {
	while (*unicode) {
		*ascii++ = *unicode++;
	}
	*ascii = 0;
	return ascii;
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
// thanks stack overflow user242579
float atof(char * arr) {
	float val = 0;
	int afterdot = 0;
	float scale = 1;
	int neg = 0;

	if (*arr == '-') {
		arr++;
		neg = 1;
	}
	while (*arr) {
		if (afterdot) {
			scale = scale/10;
			val = val + (*arr-'0')*scale;
		} else {
			if (*arr == '.') {
				afterdot++;
			} else {
				val = val * 10.0 + (*arr - '0');
			}
		}
		arr++;
	}
	if (neg) {
		return -val;
	} else {
		return  val;
	}
}


int memcmp(void * x, void * y, size_t length) {
	uint8_t * xb = x;
	uint8_t * yb = y;
	while (length--) {
		if (*xb++ != *yb++) {
			return 1;
		}
	}
	return 0;
}

int strcmp(char * x, char * y) {
	int i = 0;
	while (x[i] != 0 && y[i] != 0) {
		if (x[i] != y[i]) {
			return 1;
		}
		i++;
	}
	return x[i] != 0 || y[i] != 0;
}

int strcasecmp(char * x, char * y) {
	int i = 0;
	while (x[i] != 0 && y[i] != 0) {
		if (tolower(x[i]) != tolower(y[i])) {
			return 1;
		}
		i++;
	}
	return x[i] != 0 || y[i] != 0;
}

int strncasecmp(char * x, char * y, size_t n) {
	int i = 0;
	while (x[i] != 0 && y[i] != 0 && n != 0) {
		if (tolower(x[i]) != tolower(y[i])) {
			return 1;
		}
		i++;
		n--;
	}
	if (n == 0) {
		return 0;
	}
	return x[i] != 0 || y[i] != 0;
}

int strncmp(char * x, char * y, size_t n) {
	int i = 0;
	while (x[i] != 0 && y[i] != 0 && n != 0) {
		if (x[i] != y[i]) {
			return 1;
		}
		i++;
		n--;
	}
	if (n == 0) {
		return 0;
	}
	return x[i] != 0 || y[i] != 0;
}

int strlen(const char * string) {
	int i = 0;
	while (*string++) {
		i++;
	}
	return i;
}

uint16_t * ustrcpy(uint16_t * dest, uint16_t * src) {
	return memcpy(dest, src, (ustrlen(src) * 2) + 2);
}

char * strcpy(char * dest, char * src) {
	return memcpy(dest, src, strlen(src) + 1);
}

char * strncpy(char * dest, char * src, size_t n) {
	int len = strlen(src);
	memset(dest, 0, n); // throw away performance to fit standard
	if (len < n) {
		return memcpy(dest, src, len + 1);
	}
	memcpy(dest, src, n);
	dest[n] = 0;
	return dest;
}

int ustrlen(const uint16_t * string) {
	int i = 0;
	while (*string++) {
		i++;
	}
	return i;
}

char * strdup(char * string) {
	if (!string) {
		return NULL;
	}
	int size = strlen(string);
	char * new = malloc(size + 1);
	memcpy(new, string, size + 1);
	return new;
}

uint16_t * ustrdup(uint16_t * string) {
	if (!string) {
		return NULL;
	}
	int size = ustrlen(string);
	uint16_t * new = malloc((size * 2) + 2);
	memcpy(new, string, (size * 2) + 2);
	return new;
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

void * memcpy32(void * dest, const void * src, size_t length) {
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
