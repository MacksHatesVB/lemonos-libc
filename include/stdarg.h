#pragma once

#define __va_argsiz(t) (((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define va_arg(ap, t)   \
	(((ap) = (ap) + __va_argsiz(t)),    \
	*((t *) (void *) ((ap) - __va_argsiz(t))))

#define va_start(ap, pN) ((ap) = ((va_list) __builtin_next_arg(pN)))
#define va_copy(d, s) ((d) = (s))
#define va_end(ap) (0)

typedef char * va_list;
