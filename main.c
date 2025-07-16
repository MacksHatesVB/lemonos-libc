#include <stdio.h>
#include <string.h>

// program which depends on elf relocations

char * strings[] = {
	"hey", "hello", "hi", "yello"
};

int main(int argc, char * argv[]) {
	for (int i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
		printf("%s\n", strings[i]);
	}
}
