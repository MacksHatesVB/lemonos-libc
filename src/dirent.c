#include <sys/syscall.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>

int getdents(int fd, dirent_t * dirents, uint32_t count) {
	return syscall(SYSCALL_GETDENTS, fd, dirents, count);
}

DIR * fdopendir(int fd) {
	if (fd < 0) {
		return NULL;
	}
	DIR * dir = malloc(sizeof(DIR));
	dir->fd = fd;
	dir->dirents = malloc(DIRENTS_BUFFER_SIZE);
	dir->offset = 0;
	dir->read = 0;
	return dir;
}

DIR * opendir(char * name) {
	return fdopendir(open(name, O_RDONLY));
}

struct dirent * readdir(DIR * dir) {
	if (dir->read == 0) {
		dir->read = getdents(dir->fd, dir->dirents, DIRENTS_BUFFER_SIZE);
		dir->offset = 0;
	}
	if (dir->read <= 0) {
		return NULL;
	}
	dirent_t * dirent = dir->dirents + dir->offset;
	dir->offset += dirent->d_reclen;
	dir->read -= dirent->d_reclen;
	return (struct dirent *) dirent;
}

int closedir(DIR * dir) {
	free(dir->dirents);
	close(dir->fd);
	free(dir);
	return 0;
}
