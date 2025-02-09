#pragma once

#include <stdint.h>

enum {
	LCTL_MULTIBOOT_MAGIC = 0,
	LCTL_CPU_TYPE_MAGIC,
	LCTL_CPU_VENDOR_MAGIC,
	LCTL_PERF_STATE_MAGIC,
	LCTL_REQUEST_FRAMEBUFFER,
};

uint32_t lctl(int number);
