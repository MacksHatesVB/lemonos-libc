#include <locale.h>
#include <stdlib.h>
#include <runtime.h>
#include <sys/syscall.h>

int get_locale() {
	if (!__is_lemonos) {
		return 0;
	}
	return syscall(SYSCALL_GETLOCALE);
}

void __locale_init() {
}
