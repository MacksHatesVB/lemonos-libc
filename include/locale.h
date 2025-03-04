#pragma once

#include <stdint.h>
#include <events.h>

enum {
	LOCALE_ENGLISH = 0,
	LOCALE_GREEK,
	LOCALE_SPANISH,
	LOCALE_RUSSIAN,
	LOCALE_KOREAN,
	LOCALE_GERMAN,
	LOCALE_NORWEGIAN,
	LOCALE_ITALIAN,
};

uint16_t event_to_char(kbd_event_t * event, int force_layer);
uint16_t (*get_layout(int layer))[][98];
int get_locale();
void __locale_init();
