#pragma once

#include <stdint.h>

#define LOG_ERROR 1
#define LOG_ITERATIONS 0xff

// vect

typedef struct {
        float x;
        float y;
} vect_2d_t;

typedef struct {
        float x;
        float y;
        float z;
} vect_3d_t;

// triangle

typedef struct {
        vect_2d_t a;
        vect_2d_t b;
        vect_2d_t c;
        uint32_t colour;
} tri_2d_t;

typedef struct {
        vect_3d_t a;
        vect_3d_t b;
        vect_3d_t c;
        uint32_t colour;
} tri_3d_t;

// matrix

typedef struct {
        float v[4][4];
} mat4x4_t;

typedef struct {
        float v[4];
} mat4x1_t;

typedef struct {
        float v[3][3];
} mat3x3_t;

typedef struct {
        float v[3];
} mat3x1_t;

void mat3x3_mul_max3x1(mat3x3_t * x, mat3x1_t * y);

float fcos(float x);
float fsin(float x);

double deg2rad(double deg);
double rad2deg(double rad);

float min2(float x, float y);
float min3(float x, float y, float z);
float max2(float x, float y);
float max3(float x, float y, float z);

uint32_t round32(uint32_t x, uint32_t y);
int scale_range32(int value, int xMin, int xMax, int yMin, int yMax);
int abs32(int x);
signed short abs16(signed short x);
signed char abs8(signed char x);
long double logl(long double base, long double number);
float pow(float, float);
long double powl(long double, long double);
uint64_t memory_scale(uint64_t bytes, int divisor);
char memory_suffix(uint64_t bytes, int divisor);
