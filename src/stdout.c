#include <sys/prctl.h>
#include <stdint.h>
#include <runtime.h>

int hook_stdout(uint64_t pid, void * handler, void * constructor) {
	if (!__is_lemonos) {
		return -1;
	}
	prctl(PR_HOOK_STDOUT, pid & 0xffffffff, pid >> 32, handler, constructor);
	return 0;
}
