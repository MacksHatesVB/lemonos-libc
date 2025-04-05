#include <font.h>
#include <lctl.h>
#include <runtime.h>
#include <stdio.h>
#include <graphics.h>
#include <stdint.h>
#include <stdlib.h>

void font_legacy_drawer(uint32_t * fb, uint16_t chr, uint32_t colour, uint32_t position) {
	uint32_t legacy_colour[16] = {
		0x000000,
		0x0000aa,
		0x00aa00,
		0x00aaaa,
		0xaa0000,
		0xaa00aa,
		0xaa5500,
		0xaaaaaa,
		0x555555,
		0x5555ff,
		0x55ff55,
		0x55ffff,
		0xff5555,
		0xff55ff,
		0xffff55,
		0xffffff
	};
	if (chr == 1) {
		fb[position] = colour | 0xff000000;
	} else if (chr > 1) {
		fb[position] = legacy_colour[chr] | 0xff000000;
	}
}

void font_blank_drawer(uint32_t * fb, uint16_t chr, uint32_t colour, uint32_t position) {
	fb[position] = 0;
}

void font_combining_drawer(uint32_t * fb, uint16_t chr, uint32_t colour, uint32_t position) {
	font_legacy_drawer(fb, chr, colour, position - 8);
}

void font_truecolour_drawer(uint32_t * fb, uint16_t chr, uint32_t colour, uint32_t position) {
	if (chr & 0xff000000) {
		fb[position] = chr | 0xff000000;
	}
}

font_drawer_t font_get_drawer(uint32_t control) {
	switch (control) {
		case FONT_LEGACY:
			return font_legacy_drawer;
		case FONT_BLANK:
			return font_blank_drawer;
		case FONT_COMBINING:
			return font_combining_drawer;
		case FONT_TRUECOLOUR:
			return font_truecolour_drawer;
	}
	return font_legacy_drawer;
}

uint32_t font_address(font_t * font, uint16_t codepoint) {
	uint32_t address = 0;
	while ((font->bitmaps[address] != codepoint) && address < font->size) {
		address += 130;
	}
	if (address >= font->size) {
		return font->size - 130;
	}
	return address;
}

uint32_t * font_get(font_t * font, uint16_t codepoint) {
	uint32_t address = font_address(font, codepoint);
	return &font->bitmaps[address];
}

font_t * font_make_handle(void * bitmaps, uint32_t size) {
	font_t * font = malloc(sizeof(font_t));
	font->bitmaps = bitmaps;
	font->size = size;
	return font;
}

int font_contains(font_t * font, uint16_t codepoint) {
	uint32_t address = font_address(font, codepoint);
	return font->bitmaps[address] == codepoint;
}

void font_draw_line(uint32_t * character, int offset, uint32_t colour, uint32_t * fb, font_drawer_t drawer, uint32_t line) {
	for (int i = 0; i < 8; i++) {
		uint32_t code = character[offset + i];
		if (code == 0) {
			continue;
		}
		drawer(fb, code, colour, line + i);
	}
}

void font_draw(uint32_t * character, uint32_t colour, int x, int y, int width, uint32_t * fb) {
	int i = 2;
	font_drawer_t drawer = font_get_drawer(character[1]);
	for (int j = 0; j < 16; j++) {
		int line = x + (y++ * width);
		font_draw_line(character, i, colour, fb, drawer, line);
		i += 8;
	}
}

void font_draw_string(font_t * font, uint16_t * string, uint32_t colour, int x, int y, int width, uint32_t * fb) {
	uint16_t chr;
	while (chr = *string) {
		uint32_t * character = font_get(font, chr);
		font_draw(character, colour, x, y, width, fb);
		x += 8;
		string++;
	}
}

font_t * font_load() {
	uint32_t * bitmaps;
	uint32_t size;
	if (__is_lemonos) {
		bitmaps = (uint32_t *) lctl(LCTL_FONT_GET_BITMAPS);
		size = lctl(LCTL_FONT_GET_SIZE);
	} else {
		FILE * fp = fopen("/usr/local/lib/i386-lemonos/font.ltf", "r");
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		bitmaps = malloc(size);
		fread(bitmaps, size, 1, fp);
		fclose(fp);
		size /= 4;
	}
	return font_make_handle(bitmaps, size);
}
