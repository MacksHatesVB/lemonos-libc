#include <runtime.h>
#include <stdio.h>
#include <string.h>
#include <types.h>
#include <argv.h>
#include <math.h>
#include <ctype.h>

void callback(void * priv, args_option_t * option, int value, int present) {
	if (!present) {
		return;
	}
	printf("%r %r %r\n", option->short_name, value, present);
}

int main(int argc, char * argv[]) {
	args_progspec_t spec[] = {
		"LemonOS coreutils", "1.0", "Lemon", NULL,
		"unlicense: <https://unlicense.org>",
		"This is public domain software: you are free to change and redistribute it.",
		"There is NO WARRANTY, to the extent permitted by law.",
		"Call bios functions from cmdline."
	};
	args_option_t options[] = {
		{0,   NULL,	1, TYPE_INT, 0, callback, .help="unnamed"},
		{'n', "name",	1, TYPE_INT, 0, callback, .help="named"},
		{1,   NULL,	1, TYPE_INT, 0, callback, .help="positional"},
	};
	int options_count = sizeof(options) / sizeof(options[0]);
	args_setup(ARG_DEFAULT_TO_HELP);
	args_set_help_character('\0');
	args_load_spec(spec);
	if (args_parse(argc, argv, options_count, options, NULL)) {
		return -1;
	}

	args_unsetup();
	return 0;
}
