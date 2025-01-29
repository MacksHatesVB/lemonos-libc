#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdint.h>

uint32_t waitpid(uint32_t pid, int * status, int options) {
	return syscall(SYSCALL_WAITPID, pid, status, options);
}
