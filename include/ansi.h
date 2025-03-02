#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct ansi_state ansi_state_t;

typedef void (* ansi_write_t)(ansi_state_t * state, void * buffer, size_t size);

typedef struct ansi_state {
	int state;
	int buffer[8];
	int idx;
	uint32_t colour;
	ansi_write_t write;
} ansi_state_t;

enum {
	ANSI_STATE_PRINTING = 0b00000001,
	ANSI_STATE_ESCAPE   = 0b00000010,
	ANSI_STATE_BRACKET  = 0b00000100,
	ANSI_STATE_VALUE    = 0b00001000,
	ANSI_STATE_END      = 0b00010000,
};
