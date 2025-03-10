#include <ansi.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <multitasking.h>

uint32_t ansi_decode_colour(int code) {
	uint32_t colours[] = { 0xff000000, 0xffcc0000, 0xff009a00, 0xffc4a000, 0xff0065a4, 0xff75507b, 0xff00989a, 0xffd0d0d0 };
	if (code < 30 || code > 37) {
		return 0;
	}
	code -= 30;
	return colours[code];
}

void ansi_decode_sequence(ansi_state_t * state, int * ansi_buffer, int length) {
	if (length < 1) {
		state->colour = 0xffffffff;
		return;
	}
	int code = *ansi_buffer;
	switch (code) {
		case 0:
			if (length < 2) {
				return;
			}
			uint32_t colour = ansi_decode_colour(ansi_buffer[1]);
			if (!colour) {
				return;
			}
			state->colour = colour;
			return;
		case 38:
			if (length < 5 || ansi_buffer[1] != 2) {
				return;
			}
			uint8_t r = ansi_buffer[2];
			uint8_t g = ansi_buffer[2];
			uint8_t b = ansi_buffer[2];
			state->colour = 0xff000000 | (r << 16) | (g << 8) | b;
			return;
	}
}

ssize_t ansi_decode(ansi_state_t * state, uint16_t * buffer, size_t size) {
	while (size--) {
		uint16_t chr = *buffer;
		switch (state->state) {
			case ANSI_STATE_PRINTING:
				if (chr == 0x1b) {
					state->state = ANSI_STATE_ESCAPE;
					break;
				}
				state->write(state, &chr, 1);
				break;
			case ANSI_STATE_ESCAPE:
				if (chr == u'[') {
					state->state = ANSI_STATE_BRACKET;
					break;
				}
				state->state = ANSI_STATE_PRINTING;
				break;
			case ANSI_STATE_BRACKET:
				state->idx = 0;
				state->state = ANSI_STATE_VALUE;
				break;
			case ANSI_STATE_VALUE:
				state->buffer[state->idx] = ustrtol(buffer);
				buffer = ustrnexti(buffer) - 1;
				state->idx++;
				state->state = ANSI_STATE_END;
				break;
			case ANSI_STATE_END:
				if (chr == ';') {
					state->state = ANSI_STATE_VALUE;
				} else if (chr == 'm') {
					ansi_decode_sequence(state, state->buffer, state->idx);
					state->state = ANSI_STATE_PRINTING;
				}
				break;
		}
		buffer++;
	}
	return 0;
}

void ansi_default_writer(ansi_state_t * state, void * buffer, size_t size) {
	write(1, buffer, size);
}

void ansi_set_writer(process_t * process, ansi_write_t write) {
	ansi_state_t * state = process->stdout_priv;
	state->write = write;
}

void ansi_set_priv(process_t * process, void * priv) {
	ansi_state_t * state = process->stdout_priv;
	state->priv = priv;
}

void ansi_constructor(process_t * process) {
	ansi_state_t * state = malloc(sizeof(ansi_state_t));
	state->state = ANSI_STATE_PRINTING;
	state->idx = 0;
	state->colour = 0xffffffff;
	state->write = ansi_default_writer;
	process->stdout_priv = state;
}

ssize_t ansi_handler(process_t * process, uint16_t * buffer, size_t size) {
	// this is an evil hack that lets us pass privs to our decoder
	// todo: better API ?
	ansi_state_t * state = process->stdout_priv;

	ansi_decode(state, buffer, size);
}
