#include <graphics.h>
#include <unistd.h>

uint8_t degrade_step(uint8_t c, uint8_t t) {
	if (c == t) {
		return c;
	}
	c -= 1;
	if (t > c) {
		c += 2;
	}
	return c;
}

uint32_t rgb_degrade(uint32_t colour, uint32_t target) {
	uint8_t r, g, b;
	uint8_t tr, tg, tb;
	r = colour >> 16;
	g = colour >> 8;
	b = colour;
	tr = target >> 16;
	tg = target >> 8;
	tb = target;
	colour |= 0xff000000;
	target |= 0xff000000;
	if (target == colour) {
	        return target;
	}
	r = degrade_step(r, tr);
	g = degrade_step(g, tg);
	b = degrade_step(b, tb);
	return (r << 16) | (g << 8) | b | 0xff000000;
}

// from gdk-pixbuf (gdk-pixbuf/pixops/pixops.c)
uint32_t alpha_calculate(uint32_t top, uint32_t bottom) {
        uint32_t alpha = top >> ALPHA_SHIFT; // grab the alpha value
        uint32_t inverted = COLOUR_MASK - alpha; // invert it (80% of the top == 20% of the bottom)
        uint32_t top_r = (top >> RED_SHIFT) & COLOUR_MASK; // grab all the top's rgb values
        uint32_t top_g = (top >> GREEN_SHIFT) & COLOUR_MASK;
        uint32_t top_b = (top >> BLUE_SHIFT) & COLOUR_MASK;
        uint32_t bottom_r = (bottom >> RED_SHIFT) & COLOUR_MASK; // grab the bottom's rgb values
        uint32_t bottom_g = (bottom >> GREEN_SHIFT) & COLOUR_MASK;
        uint32_t bottom_b = (bottom >> BLUE_SHIFT) & COLOUR_MASK;
        uint32_t output = 0;
        uint32_t tmp = 0; // result

        // multiply each RGB component by the alpha value
        // the result is the same as regular alpha calculation but times 256
        // the result is also 1 off so we have to add 256 (1 * 256) to it
        tmp = (alpha * top_r) + (inverted * bottom_r) + 256;

        output |= (tmp << 8) & RED_MASK; // shift into place and mask out the garbage
        tmp = (alpha * top_g) + (inverted * bottom_g) + 256;
        output |= tmp & GREEN_MASK; // mask out the garbage
        tmp = (alpha * top_b) + (inverted * bottom_b) + 256;
        output |= tmp >> 8; // shift over to blue
        output |= ALPHA_MASK; // make it opaque
        return output;
}

window_t * create_window(uint16_t * title, uint16_t * progname, int width, int height) {
	volatile window_spec_t windowspec;
	windowspec.title = title;
	windowspec.taskbar_text = progname;
	windowspec.width = width;
	windowspec.height = height;

	// todo: something else later
	ipc(3, 0, (void *) &windowspec);

	return windowspec.output;
}
