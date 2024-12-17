#include <multiboot.h>
#include <sys/syscall.h>
#include <stdlib.h>

multiboot_header_t * multiboot_get_header() {
	return (multiboot_header_t *) (uint32_t) syscall(SYSCALL_LCTL, LCTL_MULTIBOOT_MAGIC);
}
