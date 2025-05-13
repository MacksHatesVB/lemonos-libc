#pragma once

#include <time.h>
#include <sys/types.h>

struct stat {
	uint32_t st_dev;
	uint32_t st_ino;
	mode_t st_mode;
	uint32_t st_nlink;
	uint32_t st_uid;
	uint32_t st_gid;
	uint32_t st_rdev;
	unsigned long st_size;
	unsigned long st_blksize;
	unsigned long st_blocks;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
};

int stat(char * name, struct stat * statbuf);
int fstat(int fd, struct stat * statbuf);
int mkdir(char * path, unsigned int mode);
int rmdir(char * path);
