#pragma once

#include <stdint.h>
#include <math.h>

enum CHARACTER_TYPES {
	FONT_LEGACY,
	FONT_BLANK,
	FONT_COMBINING,
	FONT_TRUECOLOUR = 16,
};

#define COLOUR_MASK 0xff

#define RED_MASK 0xff0000
#define GREEN_MASK 0x00ff00
#define BLUE_MASK 0x0000ff
#define ALPHA_MASK 0xff000000

// half life reference
#define BLUE_SHIFT 0
#define GREEN_SHIFT 8
#define RED_SHIFT 16
#define ALPHA_SHIFT 24

typedef int (* gfx_callback_t)();

typedef struct size_2d {
	int width;
	int height;
} size_2d_t;

typedef struct _rect_2d {
	int x;
	int y;
	vect_2d_t cursor;
	uint32_t * fb;
	size_2d_t size;
	int bpp;
	int updated;
} rect_2d_t;

typedef struct {
	uint32_t * icon;
	uint16_t * text;
	gfx_callback_t click;
	gfx_callback_t contextmenu;
	gfx_callback_t textupdate;
	// misnomer
	int x;
	int y;
} taskbar_button_t;

typedef struct _window {
	rect_2d_t rect;
	uint16_t * text;
	rect_2d_t text_rect;
	int id;
	int x;
	int y;
} window_t;

typedef struct {
	uint16_t * title;
	uint16_t * taskbar_text;
	int width;
	int height;
	window_t * output;
} window_spec_t;

extern int legacy_colour[16];

uint32_t rgb_degrade(uint32_t colour, uint32_t target);
uint32_t alpha_calculate(uint32_t top, uint32_t bottom);
window_t * create_window(uint16_t * title, uint16_t * progname, int width, int height);
