#include <argv.h>
#include <types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

static args_settings_t settings;

int args_contains(int argc, char * argv[], char * needle) {
	int i = 0;
	for (char * arg = argv[0]; i < argc; arg = argv[i]) {
		if (strcmp(arg, needle) == 0) {
			return 1;
		}
		i++;
	}
	return 0;
}

int args_contains_long(int argc, char * argv[], char * shortname, char * longname) {
	return args_contains(argc, argv, shortname) || args_contains(argc, argv, longname);
}

// return if an argument is valid
// -a    == valid
// --a   == valid
// --abc == valid
// -abc  == invalid
// -     == invalid
// --    == invalid
// a     == invalid
// abc   == invalid
// note: this is kinda stupid?
int args_is_valid(char * arg, int size) {
	if (size < 2) {
		return 0;
	}
	if (arg[0] != '-') {
		return 0;
	}
	if ((arg[1] == '-') && size < 3) {
		return 0;
	}
	if ((arg[1] != '-') && size > 2) {
		return 0;
	}
	return arg[0] == '-';
}

args_option_t * args_find(char * arg, int optionc, args_option_t * options) {
	int is_short = arg[1] != '-'; // arg is always 2 chars long so this is fine
	char short_name = arg[1]; // grab the character
	char * long_name = arg + 2; // get past --
	switch (is_short) {
		case 1:
			if (options->short_name == 0) {
				return NULL; // deactivated
			}
			for (int i = 0; i < optionc; i++) {
				args_option_t * option = &options[i];
				if (option->short_name == short_name) {
					return option;
				}
			}
			break;
		case 0:
			if (!options->long_name) {
				return NULL; // deactivated
			}
			for (int i = 0; i < optionc; i++) {
				args_option_t * option = &options[i];
				if (strcmp(option->long_name, long_name) == 0) {
					return option;
				}
			}
			break;
	}
	return NULL;
}

char * args_get_argument(int argc, char * argv[], int next, args_option_t * option) {
	if (!option->wants_argument || (next >= argc)) {
		return NULL; // exhausted
	}
	char * arg = argv[next];
	int size = strlen(arg);
	if (!settings.allow_option_arguments && args_is_valid(arg, size)) {
		return NULL;
	}
	return arg;
}

void safe_print(char * string, char end) {
	if (!string) {
		return;
	}
	printf("%s", string);
	putc(end);
}

// bootiful!
void args_print_help(int argc, char * argv[], int optionc, args_option_t * options) {
	char * name = (argc >= 1) ? basename(argv[0]) : "PROGNAME"; // LemonOS for example can call us with __nothing__ in argv, so do this
	args_option_t * option = NULL;
	printf("Usage: %s [OPTION]...", name);
	if (option = args_find("-\x01", optionc, options)) {
		printf(" [%s]", option->help);
	}
	printf("\n");
	safe_print(settings.description, '\n');
	printf("\n");
	for (int i = 0; i < optionc; i++) {
		args_option_t * option = &options[i];
		if (option->short_name == 1) {
			continue;
		}
		int tab_length = 22 - (option->long_name ? strlen(option->long_name) : 0); // todo: handle this a little differently (and make this stdlib function?)
		printf((option->short_name == 0) ? "      " : "  -%c%c ", option->short_name, option->long_name ? ',' : ' ');
		printf(option->long_name ? "--%s" : "  ", option->long_name);
		while (tab_length-- > 0) { putc(' '); } // yeah
		safe_print(option->help, '\0');
		printf("\n");
	}
	printf("  -%c, --help     display this help and exit\n", settings.help_char);
	printf("  -%c, --version  output version information and exit\n\n", settings.version_char);
	if (settings.license) {
		printf("License %s\n", settings.license); // print their licesense (if they set one)
	}
	printf("LemonOS stdlib license: <https://unlicense.org>\n"); // then ours
}

// kind messy
void args_print_version(int argc, char * argv[]) {
	char * name = (argc >= 1) ? basename(argv[0]) : "PROGNAME"; // LemonOS for example can call us with __nothing__ in argv, so do this
	printf("%s ", name);
	if (settings.package) {
		printf("(%s) ", settings.package);
	}
	safe_print(settings.version, '\0');
	printf("\n");
	safe_print(settings.copyright, '\n');
	if (settings.license) {
		printf("License %s\n", settings.license);
	}
	safe_print(settings.disclaimer, '\n');
	safe_print(settings.warranty, '\n');
	if (settings.author) {
		printf("\nWritten by %s\n", settings.author);
	}

	printf("\n");
	printf("LemonOS stdlib license: <https://unlicense.org>\n"); // then ours
}

int args_type_check(char * arg, args_option_t * option) {
	if (option->type == TYPE_NULL) {
		return 1;
	}
	if (settings.allow_bad_types || ((option->flags & ARG_DISABLE_CHECKS) != 0) || option->type == TYPE_BOOL) {
		return 0;
	}
	return guess_string_type(arg) == TYPE_STRING;
}

void args_call_callback(void * p, args_option_t * option, char * arg, void * priv) {
	// todo: remove the amount of ifs, holy moly
	if (option->wants_argument && !arg && (option->flags & ARG_ARGUMENT_REQUIRED) != 0) {
		return;
	}
	if (option->type == TYPE_BOOL) {
		args_bool_callback_t callback = (args_bool_callback_t) p;
		if (option->wants_argument) {
			int b = string2bool(arg);
			if (b == -1) {
				callback(priv, option, 0);
				return;
			}
			callback(priv, option, b);
			return;
		}
		callback(priv, option, (option->flags & ARG_FOUND) != 0);
		return;
	}
	if (!option->wants_argument) {
		args_int_callback_t callback = (args_int_callback_t) p;
		callback(priv, option, 0, 0);
		return;
	}
	if (settings.no_casts || ((option->flags & ARG_NO_CASTS) != 0) || option->type == TYPE_NULL) {
		args_int_callback_t callback = (args_int_callback_t) p;
		callback(priv, option, (int) arg, 1);
		return;
	}
	switch (option->type) {
		case TYPE_STRING: {
			args_string_callback_t callback = (args_string_callback_t) p;
			callback(priv, option, arg); // :shrug:
			break;
		}
		case TYPE_INT: {
			args_int_callback_t callback = (args_int_callback_t) p;
			if (!arg) {
				callback(priv, option, 0, 0);
				break;
			}
			callback(priv, option, atoi(arg), 1);
			break;
		}
		case TYPE_FLOAT: {
			args_float_callback_t callback = (args_float_callback_t) p;
			if (!arg) {
				callback(priv, option, 0, 0);
				break;
			}
			callback(priv, option, atof(arg), 1);
			break;
		}
	}
}

int args_is_help(char * arg, int size) {
	if (arg[1] == settings.help_char && size == 2) {
		return 1;
	}
	return strcmp(arg + 2, "help") == 0;
}

int args_is_version(char * arg, int size) {
	if (arg[1] == settings.version_char && size == 2) {
		return 1;
	}
	return strcmp(arg + 2, "version") == 0;
}

// shit
int args_option_find_index(int optionc, args_option_t * haystack, args_option_t * needle) {
	for (int i = 0; i < optionc; i++) {
		args_option_t * p = &haystack[i];
		if (p == needle) {
			return i;
		}
	}
	return -1;
}

int args_handle_builtins(int argc, char * argv[], int optionc, args_option_t * options) {
	int i = 1;
	if (settings.silent) {
		return 0;
	}
	for (char * arg = argv[1]; i < argc; arg = argv[i]) {
		int size = strlen(arg);
		if (!args_is_valid(arg, size)) {
			i++;
			continue;
		}
		if (args_is_help(arg, size)) {
			args_print_help(argc, argv, optionc, options);
			return 1;
		}
		if (args_is_version(arg, size)) {
			args_print_version(argc, argv);
			return 1;
		}
		i++;
	}
	return 0;
}

int args_was_found(char * arg, int optionc, args_option_t * options) {
	int size = strlen(arg);
	if (!args_is_valid(arg, size)) {
		return 0;
	}
	args_option_t * option = args_find(arg, optionc, options);
	return (option->flags & ARG_FOUND) != 0;
}

args_option_state_t * args_make_states(int optionc, args_option_t * options) {
	args_option_state_t * states = malloc(optionc * sizeof(args_option_state_t));
	if (!states) {
		return NULL;
	}
	memset(states, 0, optionc * sizeof(args_option_state_t));
	for (int i = 0; i < optionc; i++) {
		args_option_state_t * state = &states[i];
		state->option = &options[i];
	}
	return states;
}

int args_do_defaults(int argc, char * argv[], int optionc, args_option_t * options, int found) {
	if (settings.default_to_help && found == 0) {
		args_print_help(argc, argv, optionc, options);
		return 1;
	}
}

int args_parse(int argc, char * argv[], int optionc, args_option_t * options, void * priv) {
	int i = 1;
	int found = 0;
	char * argument = NULL; // i have a limited vocabulary, wtf do i call this ??
	args_option_state_t * states = args_make_states(optionc, options);
	if (!states) {
		return -1;
	}

	/* PRE PASS: check for help (-h, --help) */
	if (!settings.silent && args_handle_builtins(argc, argv, optionc, options)) {
		free(states);
		return 1;
	}

	/* FIRST PASS: */
	for (char * arg = argv[1]; i < argc; arg = argv[i]) {
		int size = strlen(arg);
		if (!args_is_valid(arg, size)) {
			argument = arg;
			i++;
			continue;
		}
		args_option_t * option = args_find(arg, optionc, options);
		if (!option) {
			i++;
			continue;
		}
		char * arg = args_get_argument(argc, argv, i + 1, option);
		if (args_type_check(arg, option)) {
			i++;
			continue;
		}
		option->flags |= ARG_FOUND;
		found++;
		if (settings.allow_dups) {
			args_call_callback(option->callback, option, arg, priv);
		} else {
			int index = args_option_find_index(optionc, options, option);
			if (index == -1) {
				i++;
				continue;
			}
			args_option_state_t * state = &states[index];
			state->arg = arg;
		}
		i = i + 1 + !!arg; // winner
	}

	/* POST PASS: call callbacks if de-duplicating, check if required arguments were not passed */
	for (int i = 0; i < optionc; i++) {
		args_option_state_t * state = &states[i];
		args_option_t * option = state->option;
		if ((option->flags & ARG_FOUND) == 0) {
			if ((option->flags & ARG_REQUIRED) != 0) {
				free(states);
				args_do_defaults(argc, argv, optionc, options, 0);
				return 1; // required argument not passed
			}

			// well must always call bool's callback
			if (option->type == TYPE_BOOL) {
				args_call_callback(option->callback, option, NULL, priv);
			}
			continue;
		}
		if (!settings.allow_dups) {
			args_call_callback(option->callback, option, state->arg, priv);
		}
	}

	args_option_t * option = args_find("-\x01", optionc, options);
	if (option && argument) {
		args_call_callback(option->callback, option, argument, priv);
		found++;
	}

	free(states);
	args_do_defaults(argc, argv, optionc, options, found);
	return 0;
}

void args_set_license(char * license) {
	settings.license = strdup(license);
}

void args_set_copyright(char * copyright) {
	settings.copyright = strdup(copyright);
}

void args_set_description(char * description) {
	settings.description = strdup(description);
}

void args_set_disclaimers(char * disclaimer, char * warranty) {
	settings.disclaimer = strdup(disclaimer);
	settings.warranty = strdup(warranty);
}

void args_set_author(char * author) {
	settings.author = strdup(author);
}

// both
void args_set_package(char * package, char * version) {
	settings.package = strdup(package);
	settings.version = strdup(version);
}

void args_load_spec(args_progspec_t * spec) {
	args_set_package(spec->package, spec->version);
	args_set_author(spec->author);
	args_set_copyright(spec->copyright);
	args_set_license(spec->license);
	args_set_disclaimers(spec->disclaimer, spec->warranty);
	args_set_description(spec->description);
}

// if you want to use `-V` or `-h` for yourself
void args_set_version_character(char chr) {
	settings.version_char = chr;
}

void args_set_help_character(char chr) {
	settings.help_char = chr;
}

void args_setup(uint32_t flags) {
	settings.allow_option_arguments = (flags & ALLOW_OPTIONS_AS_ARGS) != 0;
	settings.allow_bad_types = (flags & ALLOW_INCORRECT_TYPES) != 0;
	settings.default_to_help = (flags & ARG_DEFAULT_TO_HELP) != 0;
	settings.no_casts = (flags & ARG_NO_CASTS) != 0;
	settings.allow_dups = (flags & ALLOW_DUPLICATES) != 0;
	settings.silent = (flags & ARG_SILENT) != 0;

	settings.help_char = 'h';
	settings.version_char = 'V';
}

void args_unsetup() {
	// our free() can handle NULL so dont check (so can others i assume (?))
	free(settings.description);
	free(settings.copyright);
	free(settings.license);
	free(settings.author);
	free(settings.version);
	free(settings.package);
	free(settings.disclaimer);

	settings.description = NULL;
	settings.copyright = NULL;
	settings.license = NULL;
	settings.author = NULL;
	settings.version = NULL;
	settings.package = NULL;
	settings.disclaimer = NULL;
}
