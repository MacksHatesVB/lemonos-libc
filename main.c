#include <argv.h>
#include <types.h>
#include <stdio.h>

// our little callback
// todo: needs priv
void callback(void * priv, args_option_t * option, char * arg) {
	if (option->long_name) {
		printf("got: --%s", option->long_name);
	} else {
		printf("got: -%c", option->short_name);
	}
	if (arg) {
		printf(" %s", arg);
	} else if (option->wants_argument) {
		printf(" (didnt get expected argument)");
	}
	printf("\n");
}

void int_callback(void * priv, args_option_t * option, int arg, int has_arg) {
	printf("got: --%s", option->long_name);
	if (has_arg) {
		printf(" %d", arg);
	} else if (option->wants_argument) {
		printf(" (didnt get expected argument)");
	}
	printf("\n");
}

void float_callback(void * priv, args_option_t * option, float arg, int has_arg) {
	printf("got: --%s", option->long_name);
	if (has_arg) {
		printf(" %f", arg);
	} else if (option->wants_argument) {
		printf(" (didnt get expected argument)");
	}
	printf("\n");
}

void bool_callback(void * priv, args_option_t * option, int present) {
	printf("got: --%s %s\n", option->long_name, present ? "true" : "false");
}

int main(int argc, char * argv[]) {
	args_progspec_t spec[] = {
		"LemonOS stdlib", "1.0", "Lemon",
		NULL, // no copyright
		"unlicense: <https://unlicense.org>",
		"This is public domain software: you are free to change and redistribute it.",
		"There is NO WARRANTY, to the extent permitted by law.",
		"Argument test program."
	};
	args_option_t options[] = { // our pile of stuff to pass to args_parse()
		{'s', "string",	1, TYPE_STRING,	0,			callback,		.help="test argument, wants argument"},
		{'i', "int",	1, TYPE_INT,	ARG_REQUIRED,		int_callback,		.help="test argument, wants int argument (required)"},
		{'I', "int2",	1, TYPE_INT,	ARG_DISABLE_CHECKS,	int_callback,		.help="test argument, wants int argument"},
		{'f', "float",	1, TYPE_FLOAT,	ARG_ARGUMENT_REQUIRED,	float_callback,		.help="test argument, wants float argument"},
		{'F', "float2",	1, TYPE_FLOAT,	ARG_NO_CASTS,		float_callback,		.help="test argument, wants float argument"},
		{'b', "bool",	1, TYPE_BOOL,	0,			bool_callback,		.help="test argument"},
		{'B', "bool2",	1, TYPE_BOOL,	ARG_ARGUMENT_REQUIRED,	bool_callback,		.help="test argument, wants bool argument"},
		{'n', "noarg",	0, TYPE_NULL,	0,			callback,		.help="test argument"},
		{'S', NULL,	0, TYPE_NULL,	0,			callback,		.help="test argument, no long name"},
		{'\0',"noshort",0, TYPE_NULL,	0,			callback,		.help="test argument, no short name"},
		{'\0', NULL,	0, TYPE_NULL,	0,			callback,		.help="test argument, neither"},
		{'\x01',"count",1, TYPE_INT,	0,			int_callback,		.help="COUNT"},
	};
	int options_count = sizeof(options) / sizeof(options[0]);

	args_setup(ARG_DEFAULT_TO_HELP | ARG_STACK_POSITIONALS); // show help if there are no arguments
	args_load_spec(spec);
	args_parse(argc, argv, options_count, options, NULL);
	args_unsetup();
}
