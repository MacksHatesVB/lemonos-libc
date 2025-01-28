#include <stddef.h>
#include <stdio.h>

int args_contains(char * argv[], char * argument) {
	int i = 0;
	for (char * arg = argv[0]; arg != NULL; arg = argv[i++]) {
		printf("%s\n", arg);
	}
}
