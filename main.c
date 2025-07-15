#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char * argv[]) {
	FILE * fp = fopen("test.txt", "w");
	fwrite(argv[0], strlen(argv[0]), 1, fp);
	fclose(fp);
	return 0;
}
