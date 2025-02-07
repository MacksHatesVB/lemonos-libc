#pragma once

int open(char * name, int flags);
ssize_t write(int fd, const void * buf, size_t count);
ssize_t read(int fd, void * buf, size_t count);
int close(int fd);
