#pragma once

#include <stdint.h>

typedef uint32_t socklen_t;

uint16_t htons(uint16_t d);
uint32_t htond(uint32_t d);
uint16_t ntohs(uint16_t d);
uint32_t ntohd(uint32_t d);
uint32_t inet_addr(char * ip);
