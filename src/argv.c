#include <stddef.h>
#include <stdio.h>

int args_contains(char * argv[], char * needle) {
	int i = 0;
	for (char * arg = argv[0]; arg != NULL; arg = argv[i++]) {
		if (strcmp(arg, needle) == 0) {
			return 1;
		}
	}
	return 0;
}
