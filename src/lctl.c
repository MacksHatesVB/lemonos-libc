#include <sys/syscall.h>
#include <stdint.h>
#include <lctl.h>

uint32_t lctl(int number) {
	return (uint32_t) syscall(SYSCALL_LCTL, number);
}
