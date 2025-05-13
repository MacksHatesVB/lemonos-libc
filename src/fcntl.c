#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/syscall.h>

int open(char * name, int flags, ...) {
	return syscall(SYSCALL_OPEN, name, flags);
}

ssize_t write(int fd, const void * buf, size_t count) {
	return syscall(SYSCALL_WRITE, fd, buf, count);
}

ssize_t read(int fd, void * buf, size_t count) {
	return syscall(SYSCALL_READ, fd, buf, count);
}

int close(int fd) {
	return syscall(SYSCALL_CLOSE, fd);
}
