#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/syscall.h>

int uname(struct utsname * name) {
	return syscall(SYSCALL_UNAME, name);
}
