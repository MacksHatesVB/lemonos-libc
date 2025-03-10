#include <font.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	font_t * font = font_load();
	printf("%r\n", font_address(font, 'a'));
}
