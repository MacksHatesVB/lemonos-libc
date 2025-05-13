#pragma once

#include <stdint.h>
#include <stddef.h>
#include <math.h>

char * getenv(const char * name);
int cpu_get_temp();
void exit(int status);
int syscall(const int number, ...);
void * realloc(void * ptr, size_t size);
void * malloc(size_t size);
void free(void * p);
int rand();
void srand(unsigned int seed);
