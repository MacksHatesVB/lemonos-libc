#include <sys/sysinfo.h>
#include <sys/syscall.h>
#include <stdlib.h>

int sysinfo(struct sysinfo * info) {
	return syscall(SYSCALL_SYSINFO, info);
}
