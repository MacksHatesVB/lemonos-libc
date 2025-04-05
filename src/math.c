#include <math.h>
#include <stdio.h>

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

double deg2rad(double deg) {
        return deg * 0.017453292516666667;
}

double rad2deg(double rad) {
        return rad / 0.017453292516666667;
}


float min2(float x, float y) {
	return (x <= y) ? x : y;
}

float min3(float x, float y, float z) {
	if (x <= y && x <= z) {
		return x;
	}
	if (y <= x && y <= z) {
		return y;
	}
	return z;
}

float max2(float x, float y) {
	return (x >= y) ? x : y;
}

float max3(float x, float y, float z) {
	if (x >= y && x >= z) {
		return x;
	}
	if (y >= x && y >= z) {
		return y;
	}
	return z;
}


void mat3x3_mul_max3x1(mat3x3_t * x, mat3x1_t * y) {
	float xv = (x->v[0][0] * y->v[0]) + (x->v[0][1] * y->v[1]) + (x->v[0][2] * y->v[2]);
	float yv = (x->v[1][0] * y->v[0]) + (x->v[1][1] * y->v[1]) + (x->v[1][2] * y->v[2]);
	float zv = (x->v[2][0] * y->v[0]) + (x->v[2][1] * y->v[1]) + (x->v[2][2] * y->v[2]);
	y->v[0] = xv;
	y->v[1] = yv;
	y->v[2] = zv;
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


uint64_t memory_scale(uint64_t bytes, int divisor) {
	if (bytes > (divisor * 1000000)) {
		return bytes / (divisor * 1000000);
	} else if (bytes > (divisor * 1000)) {
		return bytes / (divisor * 1000);
	} else if (bytes > divisor) {
		return bytes / divisor;
	} else {
		return bytes;
	}
}

char memory_suffix(uint64_t bytes, int divisor) {
	if (bytes > (divisor * 1000000)) {
		return 'G';
	} else if (bytes > (divisor * 1000)) {
		return 'M';
	} else if (bytes > divisor) {
		return 'K';
	} else {
		return 'B';
	}
}
