#include <stdio.h>
#include <stdint.h>
#include <cpufeats.h>

enum {
        EAX,
        EBX,
        ECX,
        EDX,
};

static int sse_level = -1;
static int avx_level = -1;
static int fpu_level = -1;

void cpuid(int parameter, uint32_t * eax, uint32_t * ebx, uint32_t * ecx, uint32_t * edx) {
	asm volatile("cpuid"

		: "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
		: "a"(parameter)
	);
}

static int simd_check_cpuid(int page, uint32_t mask, uint32_t bits, int level, int reg, int * out) {
	uint32_t trash, flag, eax, ebx, ecx, edx;
	cpuid(page, &eax, &ebx, &ecx, &edx);
	switch (reg) {
		case EAX:
			flag = eax;
			break;
		case EBX:
			flag = ebx;
			break;
		case ECX:
			flag = ecx;
			break;
		case EDX:
			flag = edx;
			break;
	}
	if ((flag & mask) == bits) {
		*out = level;
	}
}

void cpu_get_vendor_name(void * vendor) {
	uint32_t eax;
	cpuid(0, &eax, vendor, vendor + 8, vendor + 4);
	((char *) vendor)[13] = 0;
}

void cpu_get_model_name(void * model) {
	uint32_t eax, trash;
	cpuid(0x80000000, &eax, &trash, &trash, &trash);
	if (eax > 0x80000004) {
		eax = 0x80000004;
	}
	for (int i = 0x80000002; i <= eax; i++) {
		cpuid(i, model, model + 4, model + 8, model + 12);
		((char *) model)[16] = 0;
		model += 16;
	}
	int len = (eax - 0x80000001) * 16;
	((char *) model)[len] = 0;
}

int cpu_supports(int flag) {
	switch (flag) {
		default:
			return 0;

		case SSE:
		case SSE2:
		case SSE3:
		case SSSE3:
		case SSE4_1:
		case SSE4_2:
		case SSE4A:
			return sse_level >= flag;

		case AVX:
		case AVX2:
			return avx_level >= flag;

		case FPU:
		case MMX:
		case AMD3DNOW:
			return fpu_level >= flag;
	}
}

void __cpufeats_init() {
	simd_check_cpuid(0x01, SSE_MASK, SSE_MASK, SSE, EDX, &sse_level);
	simd_check_cpuid(0x01, SSE2_MASK, SSE2_MASK, SSE2, EDX, &sse_level);
	simd_check_cpuid(0x01, SSE3_MASK, SSE3_MASK, SSE3, ECX, &sse_level);
	simd_check_cpuid(0x01, SSSE3_MASK, SSSE3_MASK, SSSE3, ECX, &sse_level);
	simd_check_cpuid(0x01, SSE4_1_MASK, SSE4_1_MASK, SSE4_1, ECX, &sse_level);
	simd_check_cpuid(0x01, SSE4_2_MASK, SSE4_2_MASK, SSE4_2, ECX, &sse_level);
	simd_check_cpuid(0x01, SSE4A_MASK, SSE4A_MASK, SSE4A, ECX, &sse_level);

	simd_check_cpuid(0x07, AVX_MASK, AVX_MASK, AVX, EBX, &avx_level);
	simd_check_cpuid(0x07, AVX2_MASK, AVX2_MASK, AVX2, EBX, &avx_level);

	simd_check_cpuid(0x01, FPU_MASK, FPU_MASK, FPU, EDX, &fpu_level);
	simd_check_cpuid(0x01, MMX_MASK, MMX_MASK, MMX, EBX, &fpu_level); // mmx requires fpu, so if it is supported the fpu *must* also be
	// no 3DNow check because it doesn't exist :shrug:
}
