#include <displays.h>
#include <lctl.h>

int display_listen(display_t * display, display_listen_t callback, void * priv) {
	return lctl(LCTL_DISPLAY_LISTEN, display, callback, priv);
}

display_t * display_get_default() {
	return (display_t *) lctl(LCTL_DISPLAY_GET_DEFAULT);
}

int display_resize(display_t * display, int width, int height) {
	return lctl(LCTL_DISPLAY_RESIZE, display, width, height);
}

int display_crunch(display_t * display, int bpp) {
	return lctl(LCTL_DISPLAY_CRUNCH, display, bpp);
}
