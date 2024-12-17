#include <stdint.h>

// dont fuck with these please

uint64_t cpu_read_msr(uint32_t ecx) {
	uint64_t value;
	asm volatile (
		"rdmsr"

		: "=A"(value)
		: "c"(ecx)
	);

	return value;
}

void cpu_write_msr(uint32_t ecx, uint64_t value) {
	asm volatile (
		"wrmsr"

		:: "A"(value), "c"(ecx)
	);
}
