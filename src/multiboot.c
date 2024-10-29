#include <multiboot.h>
#include <sys/syscall.h>
#include <stdlib.h>

multiboot_header_t * multiboot_get_header() {
	// call lctl() with MULTIBOOT_MAGIC so it returns the multiboot header
	return (multiboot_header_t *) (uint32_t) syscall(SYSCALL_LCTL, LCTL_MULTIBOOT_MAGIC);
}
