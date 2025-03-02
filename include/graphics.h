#pragma once

#include <stdint.h>
#include <math.h>
#include <events.h>

typedef void (* font_drawer_t)(uint32_t * fb, uint32_t chr, uint32_t colour, uint32_t position); // character drawer
typedef void (* gfx_event_callback_t)(event_t * event, void * priv);
typedef int (* gfx_callback_t)(); // generic callback for anything
typedef void (* gfx_accelerator_call_t)(); // ...

typedef struct size_2d {
	int width; // self explainitory
	int height;
} size_2d_t;

typedef struct _rect_2d {
	int x; // position (meaningless in window_t)
	int y;
	vect_2d_t cursor; // cursor position
	uint32_t * fb; // my image
	size_2d_t size; // my size
	int bpp; // my bpp (meaningless currently)
	int updated; // has my image changed (meaningless currently)
} rect_2d_t;

typedef struct {
	uint32_t * icon; // my icon image
	uint16_t * text; // my text
	gfx_callback_t onclick; // notifications
	gfx_callback_t oncontextmenu;
	gfx_callback_t ontextupdate;
	void * priv;
	// misnomer
	int x;
	int y;
} taskbar_button_t;

// dont try and fuck with some of this yourself
typedef struct _window {
	rect_2d_t rect; // my silly image
	uint16_t * text; // title
	rect_2d_t text_rect; // prerendered text optimization
	int id; // 0
	int x; //position
	int y;
	int drawx; // solve racist condition
	int drawy;
	int drawwidth; // optimisation
	int z;
	int shown; // is shown?
	int drawer;
	gfx_callback_t onopen; // notifications
	gfx_callback_t onfocus;
	gfx_callback_t onclose;
	gfx_callback_t ondraw;
	gfx_callback_t onresize;
	gfx_callback_t onmove;
	gfx_callback_t ontextupdate;
	void * priv;
	gfx_event_callback_t handle_event; // event handler
	taskbar_button_t * taskbar; // my taskbar icon
} window_t;

typedef struct {
	uint16_t * title;
	uint16_t * taskbar_text;
	int width;
	int height;
	window_t * output;
} window_spec_t;

typedef struct {
	void * fb;
	int width;
	int height;
	int bpp;
} framebuffer_spec_t;

enum {
	FONT_LEGACY,
	FONT_BLANK,
	FONT_COMBINING,
	FONT_TRUECOLOUR = 16,
};

enum {
	BPP_32BIT, // 32 bit colour
	BPP_16BIT, // 16
	BPP_8BIT, // 8
};

enum {
	WINDOW_DRAWER_DRAW, // normal draw (no transparency)
	WINDOW_DRAWER_AFDRAW, // fast transparency (1 bit)
	WINDOW_DRAWER_ADRAW, // full alpha transparency
	WINDOW_DRAWER_CKDRAW, // chroma keyed
};

enum {
	LEGACY_COLOUR_BLACK,
	LEGACY_COLOUR_BLUE,
	LEGACY_COLOUR_GREEN,
	LEGACY_COLOUR_CYAN,
	LEGACY_COLOUR_RED,
	LEGACY_COLOUR_PURPLE,
	LEGACY_COLOUR_BROWN,
	LEGACY_COLOUR_GRAY,
	LEGACY_COLOUR_DARK_GREY,
	LEGACY_COLOUR_LIGHT_BLUE,
	LEGACY_COLOUR_LIGHT_GREEN,
	LEGACY_COLOUR_LIGHT_CYAN,
	LEGACY_COLOUR_LIGHT_RED,
	LEGACY_COLOUR_LIGHT_PURPLE,
	LEGACY_COLOUR_YELLOW,
	LEGACY_COLOUR_WHITE,
};

enum {
	GFX_IPC_CREATE_WINDOW,
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

uint32_t rgb_degrade(uint32_t colour, uint32_t target);
int rgb_diff(uint32_t c1, uint32_t c2);
uint32_t alpha_calculate(uint32_t top, uint32_t bottom);
void rect_2d_draw(rect_2d_t * rect2, rect_2d_t * rect);
void rect_2d_adraw(rect_2d_t * rect2, rect_2d_t * rect);
void rect_2d_ckdraw(rect_2d_t * rect2, rect_2d_t * rect, int thresh);
framebuffer_spec_t * get_framebuffer_spec(framebuffer_spec_t * spec);
window_t * create_window(uint16_t * title, uint16_t * progname, int width, int height);
