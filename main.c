#include <ansi.h>
#include <stdio.h>

char * string = "\x1b[38;2;255;0;0mhey\x1b[0mhey";

int main(int argc, char * argv[]) {
	ansi_state_t state = {ANSI_STATE_PRINTING, {0}, 0, 0xffffffff, NULL, NULL};
	
}
