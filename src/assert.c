#include <assert.h>
#include <stdlib.h>

void assert(int expr) {
	if (!expr) {
		exit(-1);
	}
}
