#pragma once

#include <stdint.h>

#define LOG_ERROR 1
#define LOG_ITERATIONS 0xff

typedef struct vect_2d {
	int x;
	int y;
} vect_2d_t;

uint32_t round32(uint32_t x, uint32_t y);
int scale_range32(int value, int xMin, int xMax, int yMin, int yMax);
int abs32(int x);
signed short abs16(signed short x);
signed char abs8(signed char x);
long double logl(long double base, long double number);
long double pow(long double, long double);
