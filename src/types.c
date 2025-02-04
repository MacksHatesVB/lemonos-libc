#include <string.h>
#include <types.h>

// our isdigit() that also accepts `.eE`
int _my_isdigit(char chr) {
	return isdigit(chr) || chr == '.' || chr == 'E' || chr == 'e';
}

int guess_string_type(char * string) {
	int size = strlen(string);
	for (int i = 0; i < size; i++) {
		if (!_my_isdigit(string[i])) {
			return TYPE_STRING;
		}
	}
	return TYPE_INT;
}
