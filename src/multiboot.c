#include <multiboot.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <lctl.h>

multiboot_header_t * multiboot_get_header() {
	return (multiboot_header_t *) lctl(LCTL_MULTIBOOT_MAGIC);
}
