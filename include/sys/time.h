#pragma once

#include <stdint.h>

typedef struct timeval {
  uint32_t tv_sec;
  uint32_t tv_usec;
} timeval_t;

int gettimeofday(struct timeval * tv, void * tz);
