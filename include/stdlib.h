#pragma once

#include <stdint.h>
#include <stddef.h>

int cpu_get_temp();
void exit(int status);
int syscall(const int number, ...);
void * malloc(size_t size);
void free(void * p);
int rand();
void srand(unsigned int seed);
