#pragma once

#include <stdint.h>

typedef uint32_t time_t;

uint64_t get_timer_timestamp();
time_t time(time_t);
