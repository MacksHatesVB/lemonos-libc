#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

void ipc(uint64_t pid, int cmd, void * data) {
	syscall(SYSCALL_IPC, (uint32_t) pid, 0, cmd, data);
}

int reboot(int op) {
	return syscall(SYSCALL_REBOOT, op);
}

int fork() {
	return syscall(SYSCALL_FORK);
}
