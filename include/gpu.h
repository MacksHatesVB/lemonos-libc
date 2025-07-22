#pragma once

typedef struct {
	int trash; // whatever
} gpu_t;

gpu_t * gpu_autoselect();
void gpu_get_name(char * name, int size);
