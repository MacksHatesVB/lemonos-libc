#pragma once

#include <stdint.h>

uint64_t cpu_read_msr(uint32_t ecx);
void cpu_write_msr(uint32_t ecx, uint64_t value);
