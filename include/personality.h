#pragma once

#include <stdint.h>

typedef struct {
	int type;
	uint16_t * name;
	int syscall_count;
} personality_t;

enum {
	PERSONALITY_LINUX	= 0x00,
	PERSONALITY_LEMONOSv1	= 0x01,
	PERSONALITY_ROADRUNNER	= 0x02,
	PERSONALITY_NT		= 0x03, // ?
	PERSONALITY_TEMPLEOS    = 0x04,
};
