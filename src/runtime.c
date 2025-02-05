#include <runtime.h>
#include <locale.h>
#include <stdlib.h>
#include <cpufeats.h>
#include <stdio.h>

int __is_lemonos = 1;

int __attribute__((weak)) linked_main(linked_t * linked);
int __attribute__((weak)) main(int argc, char * argv[]);

// now we must initialise the runtime
int __attribute__((optimize("-O0"))) __runtime_entry(int argc, char * argv[]) {
	__is_lemonos = syscall(222) >= 0; // on any other OS 222 is undefined syscall and will return -1, on LemonOS this is getlocale() (i think?)
	__locale_init();
	__cpufeats_init();
	if (linked_main) {
		linked_t * args = linked_from_array(NULL, argv, sizeof(char *), argc);
		int ret = linked_main(args);
		linked_free(args);
		return ret;
	}
	return main(argc, argv);
}
