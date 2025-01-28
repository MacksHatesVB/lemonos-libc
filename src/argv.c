#include <stdarg.h>

int args_contains(char * argv[], char * argument) {
	for (char * arg = argv[0], int i = 0; arg != NULL; arg = argv[i++]) {
		printf("%s\n", arg);
	}
}
