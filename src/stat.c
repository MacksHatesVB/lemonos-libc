#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>

int fstat(int fd, struct stat * statbuf) {
	return syscall(SYSCALL_STAT, fd, statbuf);
}

int stat(char * name, struct stat * statbuf) {
	int fd = open(name, 0);
	int r = fstat(fd, statbuf);
	close(fd);
	return r;
}
