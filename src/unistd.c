#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

int access(char * name, int mode) {
	return syscall(SYSCALL_ACCESS, name, mode);
}

size_t lseek(int fd, long offset, int whence) {
	uint32_t result = 0;
	syscall(SYSCALL_LSEEK, fd, 0, offset, &result, whence);
	return result;
}

void ipc(uint64_t pid, int cmd, void * data) {
	syscall(SYSCALL_IPC, (uint32_t) pid, 0, cmd, data);
}

int reboot(int op) {
	return syscall(SYSCALL_REBOOT, op);
}

int fork() {
	return syscall(SYSCALL_FORK);
}

int usleep(uint32_t usec) {}
