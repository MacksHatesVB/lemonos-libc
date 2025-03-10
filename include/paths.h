#pragma once

typedef struct {
	char * token;
	int size;
	int offset;
	int token_size;
} path_iterator_t;

char * path_traverse(path_iterator_t * iterator);
