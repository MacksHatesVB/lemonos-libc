#pragma once

#include <stdint.h>

typedef struct {
	uint32_t size;
	uint32_t real_size;
	uint32_t block_size;
	void * array;
} dynarray_t;

dynarray_t * dyna_create(uint32_t size, uint32_t block_size);
dynarray_t * dyna_swap(dynarray_t * array, uint32_t size, uint32_t block_size);
dynarray_t * dyna_grow(dynarray_t * array, uint32_t size, uint32_t block_size);
dynarray_t * dyna_shrink(dynarray_t * array, uint32_t size, uint32_t block_size);
dynarray_t * dyna_reserve(dynarray_t * array, uint32_t size, uint32_t block_size);
