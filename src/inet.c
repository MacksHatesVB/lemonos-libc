#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

static char * next_digit(char * p) {
	while (*p++ != '.' && *p != 0) {}
	return p;
}

uint16_t htons(uint16_t d) {
	return (d << 8) | (d >> 8);
}

uint32_t htond(uint32_t d) {
	return ((d >> 24) & 0xff) | ((d << 8) & 0xff0000) | ((d >> 8) & 0xff00) | ((d << 24) & 0xff000000);
}

uint16_t ntohs(uint16_t d) {
	return htons(d);
}

uint32_t ntohd(uint32_t d) {
	return htond(d);
}

uint32_t inet_addr(char * ip) {
	uint32_t ret = 0;
	ret |= atoi(ip);
	ret |= atoi(ip = next_digit(ip)) << 8;
	ret |= atoi(ip = next_digit(ip)) << 16;
	ret |= atoi(ip = next_digit(ip)) << 24;
	return ret;
}
