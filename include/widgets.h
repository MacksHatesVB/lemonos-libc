#pragma once

#include <graphics.h>
#include <linked.h>
#include <events.h>
#include <font.h>

typedef struct widgets_element widgets_element_t;
typedef struct widgets_screen widgets_screen_t;

typedef void (* widgets_event_handler_t)(widgets_screen_t * screen, widgets_element_t * element, event_t * event);

typedef struct {
	int left;
	int middle;
	int right;
} widgets_mousestate_t;

typedef struct {
	int type;
	int button;
	int pressed;
	event_t * event;
} widgets_mouseevent_t;

typedef struct {
	int type;
	int x;
	int y;
	uint32_t origin;
	widgets_event_handler_t onmousedown;
	widgets_event_handler_t onmouseup;
	widgets_event_handler_t onmousemove;
	widgets_event_handler_t onclick;
} widgets_element_header_t;

typedef struct widgets_element {
	widgets_element_header_t header;
} widgets_element_t;

typedef struct {
	widgets_element_header_t header;
	rect_2d_t rect;
} widgets_element_image_t;

typedef struct {
	widgets_element_header_t header;
	uint16_t * string;
	uint32_t colour;
} widgets_element_text_t;

typedef struct {
	widgets_element_header_t header;
	int width;
	int height;
} widgets_element_hitbox_t;

typedef struct widgets_screen {
	widgets_element_header_t element_header;
	window_t * window;
	linked_t * elements;
	font_t * font;
	widgets_mousestate_t mousestate;
	widgets_element_t * focused_element;
	uint32_t background;
} widgets_screen_t;

enum {
	WIDGETS_IMAGE,
	WIDGETS_TEXT,
	WIDGETS_HITBOX,
};

enum {
	WIDGETS_ONMOUSEDOWN,
	WIDGETS_ONMOUSEUP,
	WIDGETS_ONMOUSEMOVE,
	WIDGETS_ONCLICK,
};

enum {
	WIDGETS_LEFT_BUTTON,
	WIDGETS_MIDDLE_BUTTON,
	WIDGETS_RIGHT_BUTTON,
};

enum {
	WIDGETS_TOP_LEFT     = 0b0101,
	WIDGETS_TOP_RIGHT    = 0b0110,
	WIDGETS_BOTTOM_LEFT  = 0b1001,
	WIDGETS_BOTTOM_RIGHT = 0b1010,

	WIDGETS_Y_MASK       = 0b1100,
	WIDGETS_X_MASK       = 0b0011,

	WIDGETS_TOP          = 0b0100,
	WIDGETS_BOTTOM       = 0b1000,
	WIDGETS_LEFT         = 0b0001,
	WIDGETS_RIGHT        = 0b0010,
};

enum {
	WIDGETS_WIDTH,
	WIDGETS_HEIGHT,
};

void widgets_draw_image(widgets_screen_t * screen, widgets_element_image_t * image);
widgets_element_t * widgets_create_image(void * fb, int width, int height);
widgets_element_t * widgets_create_text(uint16_t * string, uint32_t colour);
void widgets_register_handler(widgets_element_t * element, int type, void * handler);
void widgets_set_origin(widgets_element_t * element, uint32_t origin);
void widgets_position(widgets_screen_t * screen, widgets_element_t * element, int x, int y);
void widgets_add_element(widgets_screen_t * screen, widgets_element_t * element);
widgets_screen_t * widgets_create_screen(window_t * window);
void widgets_update_element(widgets_screen_t * screen, widgets_element_t * element);
void widgets_set_background(widgets_screen_t * screen, uint32_t background);
void widgets_update_screen(widgets_screen_t * screen);
