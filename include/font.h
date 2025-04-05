#pragma once

#include <stdint.h>

typedef void (* font_drawer_t)(uint32_t * fb, uint16_t chr, uint32_t colour, uint32_t position);

typedef struct {
	uint32_t * bitmaps;
	uint32_t size;
} font_t;

enum {
	FONT_LEGACY,
	FONT_BLANK,
	FONT_COMBINING,
	FONT_TRUECOLOUR = 16,
};

font_drawer_t font_get_drawer(uint32_t control);
uint32_t font_address(font_t * font, uint16_t codepoint);
uint32_t * font_get(font_t * font, uint16_t codepoint);
font_t * font_make_handle(void * bitmaps, uint32_t size);
int font_contains(font_t * font, uint16_t codepoint);
void font_draw_line(uint32_t * character, int offset, uint32_t colour, uint32_t * fb, font_drawer_t drawer, uint32_t line);
void font_draw(uint32_t * character, uint32_t colour, int y, int x, int width, uint32_t * fb);
void font_draw_string(font_t * font, uint16_t * string, uint32_t colour, int x, int y, int width, uint32_t * fb);
font_t * font_load();
