#include <unistd.h>
#include <runtime.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

int cpu_get_temp() {
	if (!__is_lemonos) {
		return 0;
	}
	return syscall(SYSCALL_GETTHERM);
}

void * brk(uintptr_t _break) {
	return (void *) (uint32_t) syscall(45, _break); // CHANGE ME
}

void * malloc(uint32_t size) {
	if (!__is_lemonos) {
		void * p = brk(0);
		void * newbrk = brk(((uintptr_t) p) + size);
		if (newbrk == (void *) -1) {
			return NULL;
		}
		return p;
	}
	return (void *) (uint32_t) syscall(SYSCALL_MALLOC, size);
}

void exit(int code) {
	syscall(SYSCALL_EXIT, code);
}

void free(void * p) {
	if (p == NULL) {
		return;
	}
	if (!__is_lemonos) {
		return;
	}
	syscall(SYSCALL_FREE, p);
}

// author: 松本 眞
// Mersenne Twister random number generator

#define STATE_SIZE  312
#define MIDDLE      156
#define INIT_SHIFT  62
#define TWIST_MASK  0xb5026f5aa96619e9
#define INIT_FACT   6364136223846793005
#define SHIFT1      29
#define MASK1       0x5555555555555555
#define SHIFT2      17
#define MASK2       0x71d67fffeda60000
#define SHIFT3      37
#define MASK3       0xfff7eee000000000
#define SHIFT4      43
#define LOWER_MASK  0x7fffffff
#define UPPER_MASK  (~(uint64_t)LOWER_MASK)

uint64_t state[STATE_SIZE];
static size_t index = STATE_SIZE + 1;

void srand(uint32_t s) {
	index = STATE_SIZE;
	state[0] = s;
	for (size_t i = 1; i < STATE_SIZE; i++) {
		state[i] = (INIT_FACT * (state[i - 1] ^ (state[i - 1] >> INIT_SHIFT))) + i;
	}
}

void twist(void) {
	for (size_t i = 0; i < STATE_SIZE; i++) {
		uint64_t x = (state[i] & UPPER_MASK) | (state[(i + 1) % STATE_SIZE] & LOWER_MASK);
		x = (x >> 1) ^ (x & 1 ? TWIST_MASK : 0);
		state[i] = state[(i + MIDDLE) % STATE_SIZE] ^ x;
	}
	index = 0;
}

int rand(void) {
	if (index >= STATE_SIZE) {
		twist();
	}
	uint64_t y = state[index];
	y ^= (y >> SHIFT1) & MASK1;
	y ^= (y << SHIFT2) & MASK2;
	y ^= (y << SHIFT3) & MASK3;
	y ^= y >> SHIFT4;
	index++;
	return y;
}
