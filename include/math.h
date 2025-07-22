#pragma once

#include <stdint.h>

#define LOG_ERROR 1
#define LOG_ITERATIONS 0xff

// constants
const double M_E        = 2.71828182845904523536;  // e
const double M_LOG2E    = 1.44269504088896340736;  // log2(e)
const double M_LOG10E   = 0.43429448190325182765;  // log10(e)
const double M_LN2      = 0.69314718055994530942;  // ln(2)
const double M_LN10     = 2.30258509299404568402;  // ln(10)
const double M_PI       = 3.14159265358979323846;  // pi
const double M_PI_2     = 1.57079632679489661923;  // pi/2
const double M_PI_4     = 0.78539816339744830962;  // pi/4
const double M_1_PI     = 0.31830988618379067154;  // 1/pi
const double M_2_PI     = 0.63661977236758134308;  // 2/pi
const double M_2_SQRTPI = 1.12837916709551257390;  // 2/sqrt(pi)
const double M_SQRT2    = 1.41421356237309504880;  // sqrt(2)
const double M_SQRT1_2  = 0.70710678118654752440;  // 1/sqrt(2)

const float MAXFLOAT   = 3.402823466e+38F;  // FLT_MAX

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
typedef union {
    double d;
    uint64_t u;
} double_cast;

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
long double pow(long double, long double);
long double powl(long double, long double);
uint64_t memory_scale(uint64_t bytes, int divisor);
char memory_suffix(uint64_t bytes, int divisor);
double ln(double);