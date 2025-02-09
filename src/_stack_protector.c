#include <stdlib.h>

void __attribute__ ((noreturn)) __stack_chk_fail_local (void) {
	exit(-1);
	while (1 == 1) {
		asm volatile ("nop");
	}
}
