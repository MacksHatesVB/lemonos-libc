#include <runtime.h>
#include <locale.h>
#include <stdlib.h>
#include <cpufeats.h>
#include <unistd.h>
#include <reloc.h>
#include <stdio.h>

int __is_lemonos = 1;

int __attribute__((weak)) linked_main(linked_t * linked);
int __attribute__((weak)) main(int argc, char * argv[]) {
	printf("This program is not an executable.\n");
}

// now we must initialise the runtime
int __attribute__((optimize("-O0"))) __runtime_entry(int argc, char * argv[]) {
	__reloc_setup();
	__is_lemonos = syscall(222) >= 0; // on any other OS 222 is undefined syscall and will return -1, on LemonOS this is getlocale() (i think?)
	__locale_init();
	__cpufeats_init();
	__stdio_init();
	write(9999, __is_lemonos ? "runtime: Assumed LemonOS" : "runtime: Assumed Linux", __is_lemonos ? 24 : 22);
	if (linked_main) {
		linked_t * args = linked_from_array(NULL, argv, sizeof(char *), argc);
		int ret = linked_main(args);
		linked_free(args);
		return ret;
	}
	return main(argc, argv);
}
