#include <sys/syscall.h>
#include <locale.h>
#include <stdlib.h>
#include <runtime.h>
#include <events.h>
#include <lctl.h>

uint16_t (*get_layout(int layer))[][98] {
	return (uint16_t (*)[][98]) lctl(LCTL_GET_LAYOUT, layer);
}

uint16_t event_to_char(kbd_event_t * event, int force_layer) {
	int layer = event->held->meta + event->held->metalock;
	int shift = event->held->lshift || event->held->rshift;
	uint16_t (* layout)[][98];
	if (force_layer != -1) {
		layer = force_layer;
	}
	layout = get_layout(layer);
	return (*layout)[shift][event->keycode];
}

int get_locale() {
	if (!__is_lemonos) {
		return 0;
	}
	return syscall(SYSCALL_GETLOCALE);
}

void __locale_init() {
}
