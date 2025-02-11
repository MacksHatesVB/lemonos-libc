#pragma once

#include <stddef.h>

typedef struct tar_header tar_header_t;

typedef int (* tar_callback_t)(tar_header_t * header, size_t size);

typedef struct tar_header {
	char filename[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char type;
} __attribute__((packed)) tar_header_t;

typedef struct {
	void * file;
	void * dirent;
} tar_handlers_t;

int tar_extract_file(tar_header_t * header, size_t size);
int tar_extract_dirent(tar_header_t * header, size_t size);
int tar_extract(tar_handlers_t * handlers, void * contents, size_t size);
