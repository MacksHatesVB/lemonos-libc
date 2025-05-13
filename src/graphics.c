#include <graphics.h>
#include <unistd.h>
#include <string.h>
#include <runtime.h>
#include <stdio.h>
#include <lctl.h>

uint8_t degrade_step(uint8_t c, uint8_t t) {
	if (c == t) {
		return c;
	}
	if (t > c) {
		return c + 1;
	}
	return c - 1;
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

int rgb_diff(uint32_t c1, uint32_t c2) {
	uint8_t r1, g1, b1;
	uint8_t r2, g2, b2;
	int dist = 0;
	int dr, dg, db;
	r1 = c1 >> 16;
	g1 = c1 >> 8;
	b1 = c1;
	r2 = c2 >> 16;
	g2 = c2 >> 8;
	b2 = c2;
	dr = abs32(r2 - r1);
	dg = abs32(g2 - g1);
	db = abs32(b2 - b1);
	dist = (dr * dr) + (dg * dg) + (db * db);
	return dist;
}

framebuffer_spec_t * get_framebuffer_spec(framebuffer_spec_t * spec) {
	if (!spec) {
		return NULL;
	}
	if (__is_lemonos) { // lol
		return (framebuffer_spec_t *) lctl(LCTL_REQUEST_FRAMEBUFFER, spec);
	}
	// how exactly do we do this on linux ?
	return NULL; // in future we can mmap /dev/fb0 i guess (?)
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

// absolutely busted, dont use
uint32_t chroma_key_calculate(uint32_t top, uint32_t bottom, uint32_t key, int thresh) {
	if (rgb_diff(top, key) < thresh) {
		return bottom;
	}
	return top;
}

void rect_2d_draw(rect_2d_t * rect2, rect_2d_t * rect) {
	uint32_t * dest;
	uint32_t * src;
	int height = rect->size.height;
	int width = rect->size.width;
	int absy = rect->y < 0 ? abs32(rect->y) : 0;
	int absx = rect->x < 0 ? abs32(rect->x) : 0;
	int pre_x = rect->x * 4;
	int pre_r2width = rect2->size.width * 4;
	int pre_rwidth = rect->size.width * 4;
	if (height + rect->y >= rect2->size.height) {
		height = rect2->size.height - rect->y;
	}
	if (width + rect->x >= rect2->size.width) {
		width = rect2->size.width - rect->x;
	}
	for (int i = absy; i < height; i++) {
		dest = (uint32_t *) (((void *) rect2->fb) + (((rect->y + i) * pre_r2width) + pre_x));
		src = (uint32_t *) (((void *) rect->fb) + (i * pre_rwidth));
		memcpy32(dest, src + absx, width - absx);
	}
	return;
}

void rect_2d_adraw(rect_2d_t * rect2, rect_2d_t * rect) {
	uint32_t * dest;
	uint32_t * src;
	int height = rect->size.height;
	int width = rect->size.width;
	int absy = rect->y < 0 ? abs32(rect->y) : 0;
	int absx = rect->x < 0 ? abs32(rect->x) : 0;
	int pre_x = rect->x * 4;
	int pre_r2width = rect2->size.width * 4;
	int pre_rwidth = rect->size.width * 4;
	if (height + rect->y >= rect2->size.height) {
		height = rect2->size.height - rect->y;
	}
	if (width + rect->x >= rect2->size.width) {
		width = rect2->size.width - rect->x;
	}
	for (int i = absy; i < height; i++) {
		dest = (uint32_t *) (((void *) rect2->fb) + (((rect->y + i) * pre_r2width) + pre_x));
		src = (uint32_t *) (((void *) rect->fb) + (i * pre_rwidth));
		for (int b = absx; b < width; b++) {
			if ((*(src + b) & 0xff000000) == 0) {
				continue;
			}
			if ((*(src + b) & 0xff000000) == 0xff000000) {
				*(dest + b) = *(src + b);
				continue;
			}
			*(dest + b) = alpha_calculate(*(src + b), *(dest + b));
		}
	}
	return;
}

void rect_2d_ckdraw(rect_2d_t * rect2, rect_2d_t * rect, int thresh) {
	uint32_t * dest;
	uint32_t * src;
	int height = rect->size.height;
	int width = rect->size.width;
	int absy = rect->y < 0 ? abs32(rect->y) : 0;
	int absx = rect->x < 0 ? abs32(rect->x) : 0;
	int pre_x = rect->x * 4;
	int pre_r2width = rect2->size.width * 4;
	int pre_rwidth = rect->size.width * 4;
	if (height + rect->y >= rect2->size.height) {
		height = rect2->size.height - rect->y;
	}
	if (width + rect->x >= rect2->size.width) {
		width = rect2->size.width - rect->x;
	}
	for (int i = absy; i < height; i++) {
		dest = (uint32_t *) (((void *) rect2->fb) + (((rect->y + i) * pre_r2width) + pre_x));
		src = (uint32_t *) (((void *) rect->fb) + (i * pre_rwidth));
		for (int b = absx; b < width; b++) {
			uint32_t top = *(src + b);
			uint32_t bottom, tmp;
			int dist = rgb_diff(top, 0x0000ff00);
			if (dist < 32) {
				continue;
			}
			if (dist > thresh) {
				*(dest + b) = top;
				continue;
			}
			bottom = *(dest + b);
			top &= 0x00ffffff;
			top |= 0xff000000 - ((top & 0x0000ff00) << 16);
			tmp = alpha_calculate(top & 0xff00ff00, 0) & 0x0000ff00;
			top &= 0xffff00ff;
			top |= tmp & 0x00ffffff;
			*(dest + b) = alpha_calculate(top, bottom); // chroma_key_calculate(*(src + b), *(dest + b), 0x00ff0000, thresh);
		}
	}
	return;
}

void rect_2d_scale(rect_2d_t * rect2, rect_2d_t * rect) {
	// rect2 == out | rect == in
	for (int y = 0; y < rect2->size.height; y++) {
		float yf = (float) y / rect2->size.height;
		int ys = yf * rect->size.height;
		for (int x = 0; x < rect2->size.width; x++) {
			float xf = (float) x / rect2->size.width;
			int xs = xf * rect->size.width;
			rect2->fb[(y * rect2->size.width) + x] = rect->fb[(ys * rect->size.width) + xs];
		}
	}
}

window_t * create_window(uint16_t * title, uint16_t * progname, int width, int height) {
	volatile window_spec_t windowspec;
	windowspec.title = title;
	windowspec.taskbar_text = progname;
	windowspec.width = width;
	windowspec.height = height;

	// todo: replace this with driver API call once that is finished
	ipc(3, 0, (void *) &windowspec);

	return windowspec.output;
}
