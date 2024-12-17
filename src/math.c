#include <math.h>

uint32_t round32(uint32_t x, uint32_t y) {
	return (x + (y - 1)) & ~(y - 1);
}

int scale_range32(int value, int xMin, int xMax, int yMin, int yMax) {
	long double tmp = ((long double) yMax - (long double) yMin) / ((long double) xMax - (long double) xMin); // multiplier
	long double absolute = value - xMin; // difference from minium value
	return yMin + (absolute * tmp);
}

long double pow(long double i, long double j) {
	return i;
}

long double logl(long double base, long double number) {
        long double v = 1;
        long double error = LOG_ERROR;
        int i = LOG_ITERATIONS;
        while (i--) {
                if (pow(base, v + error) > number) {
                        error *= 0.1;
                        if (error < 0.0000001) {
                                return v;
                        }
                        continue;
                }
                v += error;
        }
        return v;
}

int abs32(int x) {
	return ((unsigned int) x & 0x7fffffff);
}

signed short abs16(signed short x) {
	return ((unsigned short) x & 0x7fffffff);
}

signed char abs8(signed char x) {
	return ((unsigned char) x & 0x7fffffff);
}
