#include <string.h>

char * basename(char * path) {
	int size = strlen(path);
	int i = size;
	if (path[i] == '/') {
		i--;
	}
	for (; i >= 0; i--) {
		if (path[i] == '/' || path[i] == '\\') {
			return path + i + 1;
		}
	}
	return path;
}
