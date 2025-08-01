#pragma once

#include <stdint.h>

enum {
	LCTL_MULTIBOOT_MAGIC = 0,
	LCTL_CPU_TYPE_MAGIC,
	LCTL_CPU_VENDOR_MAGIC,
	LCTL_PERF_STATE_MAGIC,
	LCTL_REQUEST_FRAMEBUFFER,
	LCTL_TIMER_SET_FREQUENCY,
	LCTL_TIMER_FREQUENCY,
	LCTL_TIMER_TIMESTAMP,
	LCTL_GET_LAYOUT,
	LCTL_FONT_GET_BITMAPS,
	LCTL_FONT_GET_SIZE,
	LCTL_INITRD_LOAD,
	LCTL_GET_PCB,
	LCTL_GET_PERSONALITY,
	LCTL_GET_NAMED_PERSONALITY,

	LCTL_DISPLAY_LISTEN,
	LCTL_DISPLAY_GET_DEFAULT,
	LCTL_DISPLAY_RESIZE,
	LCTL_DISPLAY_CRUNCH,
};

uint32_t lctl(int number, ...);
