#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <dynarray.h>

dynarray_t * dyna_create(uint32_t size, uint32_t block_size) {
	dynarray_t * array = malloc(sizeof(dynarray_t));
	array->size = size;
	array->real_size = size;
	array->block_size = block_size;
	array->array = malloc(size * block_size);
}

dynarray_t * dyna_swap(dynarray_t * array, uint32_t size, uint32_t block_size) {
	if (!array) {
		return dyna_create(size, block_size);
	}
	void * new_array = malloc(size * block_size);
	memcpy(new_array, array->array, array->size * array->block_size);
	free(array->array);

	array->array = new_array;
	array->real_size = size;
	array->block_size = block_size;

	return array;
}

dynarray_t * dyna_grow(dynarray_t * array, uint32_t size, uint32_t block_size) {
	if (!array) {
		return dyna_create(size, block_size);
	}
	uint32_t new_size = array->size + size;
	return dyna_swap(array, new_size, block_size);
}

dynarray_t * dyna_shrink(dynarray_t * array, uint32_t size, uint32_t block_size) {
	if (!array) {
		return dyna_create(size, block_size);
	}
	if (size < 8) {
		return array; // not worth it
	}
	if (size >= array->size) {
		array->size = 0;
		free(array->array);
		return array;
	}
	uint32_t new_size = array->size + size;
	return dyna_swap(array, new_size, block_size);
}

dynarray_t * dyna_reserve(dynarray_t * array, uint32_t size, uint32_t block_size) {
	if (!array) {
		return dyna_create(size, block_size);
	}
	if (array->size >= size) {
		return array; // :shrug:
	}
	uint32_t new_size = array->size + round32(size - array->size, 8);
	dyna_grow(array, new_size, block_size);
	return array;
}
