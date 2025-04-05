#include <widgets.h>
#include <graphics.h>
#include <linked.h>
#include <string.h>
#include <stdlib.h>
#include <font.h>

void widgets_default_handler(widgets_screen_t * screen, widgets_element_t * element, event_t * event) {}

void widgets_draw_image(widgets_screen_t * screen, widgets_element_image_t * image) {
	rect_2d_t * window = &screen->window->rect;
	rect_2d_t * rect = &image->rect;
	rect->x = image->header.x;
	rect->y = image->header.y;
	rect_2d_adraw(window, rect);
}

int widgets_measure_image(widgets_element_image_t * image, int dimention) {
	size_2d_t * size = &image->rect.size;
	switch (dimention) {
		case WIDGETS_WIDTH:
			return size->width;
		case WIDGETS_HEIGHT:
			return size->height;
	}
}

void widgets_draw_text(widgets_screen_t * screen, widgets_element_text_t * text) {
	rect_2d_t * window = &screen->window->rect;
	uint16_t * string = text->string;
	font_draw_string(screen->font, string, text->colour, text->header.x, text->header.y, window->size.width, window->fb);
}

int widgets_measure_text(widgets_element_text_t * text, int dimention) {
	switch (dimention) {
		case WIDGETS_WIDTH:
			int length = ustrlen(text->string);
			return length * 8;
		case WIDGETS_HEIGHT:
			return 16;
	}
}

widgets_element_t * widgets_create_element(int type, int size) {
	widgets_element_t * element = malloc(size);
	element->header.type = type;
	element->header.x = 0;
	element->header.y = 0;
	element->header.origin = WIDGETS_TOP_LEFT;
	element->header.onmousedown = widgets_default_handler;
	element->header.onmouseup = widgets_default_handler;
	element->header.onmousemove = widgets_default_handler;
	element->header.onclick = widgets_default_handler;
	return element;
}

widgets_element_t * widgets_create_image(void * fb, int width, int height) {
	if (!fb) {
		fb = malloc((width * height) * 4);
	}

	widgets_element_image_t * image = (widgets_element_image_t *) widgets_create_element(WIDGETS_IMAGE, sizeof(widgets_element_image_t));
	rect_2d_t * rect = &image->rect;
	rect->size.width = width;
	rect->size.height = height;
	rect->fb = fb;
	return (widgets_element_t *) image;
}

widgets_element_t * widgets_create_text(uint16_t * string, uint32_t colour) {
	widgets_element_text_t * text = (widgets_element_text_t *) widgets_create_element(WIDGETS_TEXT, sizeof(widgets_element_text_t));
	text->string = ustrdup(string);
	text->colour = colour;
	return (widgets_element_t *) text;
}

void widgets_register_handler(widgets_element_t * element, int type, void * handler) {
	switch (type) {
		case WIDGETS_ONCLICK:
			element->header.onclick = handler;
			return;
		case WIDGETS_ONMOUSEDOWN:
			element->header.onmousedown = handler;
			return;
		case WIDGETS_ONMOUSEUP:
			element->header.onmouseup = handler;
			return;
		case WIDGETS_ONMOUSEMOVE:
			element->header.onmousemove = handler;
			return;
	}
}

void widgets_call_handler(widgets_screen_t * screen, widgets_element_t * element, int type, void * event) {
	switch (type) {
		case WIDGETS_ONCLICK:
			element->header.onclick(screen, element, event);
			return;
		case WIDGETS_ONMOUSEDOWN:
			element->header.onmousedown(screen, element, event);
			return;
		case WIDGETS_ONMOUSEUP:
			element->header.onmouseup(screen, element, event);
			return;
		case WIDGETS_ONMOUSEMOVE:
			element->header.onmousemove(screen, element, event);
			return;
	}
}

int widgets_measure_size(widgets_element_t * element, int dimention) {
	switch (element->header.type) {
		case WIDGETS_IMAGE:
			return widgets_measure_image((widgets_element_image_t *) element, dimention);
		case WIDGETS_TEXT:
			return widgets_measure_text((widgets_element_text_t *) element, dimention);
	}
}

int widgets_measure_width(widgets_element_t * element) {
	return widgets_measure_size(element, WIDGETS_WIDTH);
}

int widgets_measure_height(widgets_element_t * element) {
	return widgets_measure_size(element, WIDGETS_HEIGHT);
}

void widgets_set_origin(widgets_element_t * element, uint32_t origin) {
	element->header.origin = origin;
}

void widgets_push(widgets_element_t * element, int x, int y) {
	uint32_t origin = element->header.origin;
	uint32_t x_origin = origin & WIDGETS_X_MASK;
	uint32_t y_origin = origin & WIDGETS_Y_MASK;
	int * ex = &element->header.x;
	int * ey = &element->header.y;
	if (y_origin == WIDGETS_TOP) {
		*ey += y;
	}
	if (y_origin == WIDGETS_BOTTOM) {
		*ey -= y;
	}

	if (x_origin == WIDGETS_LEFT) {
		*ex += x;
	}
	if (x_origin == WIDGETS_RIGHT) {
		*ex -= x;
	}
}

void widgets_position(widgets_screen_t * screen, widgets_element_t * element, int x, int y) {
	uint32_t origin = element->header.origin;
	uint32_t x_origin = origin & WIDGETS_X_MASK;
	uint32_t y_origin = origin & WIDGETS_Y_MASK;
	element->header.x = (x_origin == WIDGETS_LEFT) ? 0 : (screen->window->rect.size.width - widgets_measure_width(element));
	element->header.y = (y_origin == WIDGETS_TOP) ? 0 : (screen->window->rect.size.height - widgets_measure_height(element));
	widgets_push(element, x, y);
}

void widgets_add_element(widgets_screen_t * screen, widgets_element_t * element) {
	screen->elements = linked_add(screen->elements, element);
}

static int widgets_held_to_handler(int held) {
	return held ? WIDGETS_ONMOUSEDOWN : WIDGETS_ONMOUSEUP;
}

int widgets_contains_point(widgets_element_t * element, int x, int y) {
	widgets_element_header_t * header = &element->header;
	int width = widgets_measure_width(element);
	int height = widgets_measure_height(element);
	if ((header->x > x) || (header->y > y)) {
		return 0;
	}
	if ((x > (header->x + width)) || (y > (header->y + height))) {
		return 0;
	}
	return 1;
}

widgets_element_t * widgets_search_point(widgets_screen_t * screen, int x, int y) {
	linked_iterator_t iterator = {screen->elements};
	linked_t * node = screen->elements;
	while (node) {
		widgets_element_t * element = node->p;
		if (widgets_contains_point(element, x, y)) {
			return element;
		}
		node = linked_step_iterator(&iterator);
	}
	return NULL;
}

void widgets_receive_mouseeevent(mouse_event_t * event, widgets_screen_t * screen) {
	widgets_element_t * element = widgets_search_point(screen, event->x, event->y);
	widgets_mousestate_t * state = &screen->mousestate;
	mouse_held_t * held = event->held;

	if (element == NULL) {
		element = (widgets_element_t *) screen;
	}
	if (event->delta_x != 0 || event->delta_y != 0) {
		// we need to send a move event
		widgets_call_handler(screen, element, WIDGETS_ONMOUSEMOVE, event);
	}

	if ((state->left == held->left) && (state->middle == held->middle) && (state->right == held->right)) {
		// nothing has happened to the buttons
		return;
	}
	// something happened, change focus and send events
	screen->focused_element = element;

	widgets_mouseevent_t * widgets_event = malloc(sizeof(widgets_mouseevent_t));
	widgets_event->type = EVENT_MOUSE;
	widgets_event->event = (event_t *) event;
	if (state->left != held->left) {
		widgets_event->button = WIDGETS_LEFT_BUTTON;
		widgets_event->pressed = held->left;
		widgets_call_handler(screen, element, widgets_held_to_handler(held->left), widgets_event);
	}

	if (state->middle != held->middle) {
		widgets_event->button = WIDGETS_MIDDLE_BUTTON;
		widgets_event->pressed = held->middle;
		widgets_call_handler(screen, element, widgets_held_to_handler(held->middle), widgets_event);
	}

	if (state->right != held->right) {
		widgets_event->button = WIDGETS_RIGHT_BUTTON;
		widgets_event->pressed = held->right;
		widgets_call_handler(screen, element, widgets_held_to_handler(held->right), widgets_event);
	}

	state->left = held->left;
	state->middle = held->middle;
	state->right = held->right;
	free(widgets_event);
}

void widgets_receive_event(event_t * event, void * priv) {
	widgets_screen_t * screen = priv;
	// yay
	switch (event->type) {
		case EVENT_MOUSE:
			widgets_receive_mouseeevent((mouse_event_t *) event, screen);
			return;
	}
}

widgets_screen_t * widgets_create_screen(window_t * window) {
	widgets_screen_t * screen = malloc(sizeof(widgets_screen_t));
	screen->font = font_load();
	screen->window = window;
	screen->elements = NULL;
	screen->background = 0xff000000;
	screen->focused_element = (widgets_element_t *) screen;
	screen->element_header.onmousedown = widgets_default_handler;
	screen->element_header.onmouseup = widgets_default_handler;
	screen->element_header.onmousemove = widgets_default_handler;
	screen->element_header.onclick = widgets_default_handler;
	window->handle_event = widgets_receive_event;
	window->priv = screen;
	return screen;
}

void widgets_update_element(widgets_screen_t * screen, widgets_element_t * element) {
	switch (element->header.type) {
		case WIDGETS_IMAGE:
			widgets_draw_image(screen, (widgets_element_image_t *) element);
			return;
		case WIDGETS_TEXT:
			widgets_draw_text(screen, (widgets_element_text_t *) element);
			return;
	}
}

void widgets_set_background(widgets_screen_t * screen, uint32_t background) {
	screen->background = background;
}

void widgets_update_screen(widgets_screen_t * screen) {
	if (screen->background) {
		window_t * window = screen->window;
		rect_2d_t * rect = &window->rect;
		memset32(rect->fb, screen->background, rect->size.width * rect->size.height);
	}

	linked_iterator_t iterator = {screen->elements};
	linked_t * node = screen->elements;
	while (node) {
		widgets_element_t * element = node->p;
		widgets_update_element(screen, element);
		node = linked_step_iterator(&iterator);
	}
}
