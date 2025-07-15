#pragma once

#include <stdint.h>

typedef struct dirent {
	uint32_t d_ino;
	uint32_t d_off;
	uint16_t d_reclen;
	char d_name[];
} dirent_t;

typedef struct {
	int fd;
	void * dirents;
	uint32_t offset;
	uint32_t read;
} DIR;

#define DIRENTS_BUFFER_SIZE 1024

int getdents(int fd, dirent_t * dirents, uint32_t count);
DIR * fdopendir(int fd);
DIR * opendir(char * name);
struct dirent * readdir(DIR * dir);
int closedir(DIR * dir);
