#pragma once

#include <stddef.h>
#include <stdint.h>

#define O_ACCMODE         0003
#define O_RDONLY            00
#define O_WRONLY            01
#define O_RDWR              02
#define O_CREAT           0100
#define O_EXCL            0200
#define O_NOCTTY          0400
#define O_TRUNC          01000
#define O_APPEND         02000
#define O_NONBLOCK       04000
#define O_NDELAY       O_NONBLOCK
#define O_SYNC        04010000
#define O_FSYNC         O_SYNC
#define O_ASYNC         020000
#define __O_LARGEFILE  0100000

#define R_OK 		4
#define W_OK 		2
#define X_OK 		1
#define F_OK 		0

int open(const char * name, int flags, ...);
int creat(char * name, uint32_t mode);
ssize_t write(int fd, const void * buf, size_t count);
ssize_t read(int fd, void * buf, size_t count);
int close(int fd);
