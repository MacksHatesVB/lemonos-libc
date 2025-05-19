#pragma once

#include <stdint.h>

typedef struct {
	int type;
	uint16_t * name;
	int syscall_count;
} personality_t;
