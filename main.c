#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	char name[8];
	uint8_t handle;
} lumpinfo_t;

int main(int argc, char * argv[]) {
	lumpinfo_t lumpinfo = {"", 3};
	strncpy(lumpinfo.name, "TEXTURE1", 8);
	printf("%s %d\n", lumpinfo.name, lumpinfo.handle);
}
