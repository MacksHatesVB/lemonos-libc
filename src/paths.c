#include <paths.h>
#include <stddef.h>

int path_is_separator(char chr) {
	return chr == '/' || chr == '\\' || chr == '>';
}

char * path_skip_separators(char * path) {
	while (path_is_separator(*path) && *path) {
		path++;
	}
	return path;
}

char * path_next_token(char * token) {
	while ((!path_is_separator(*token)) && *token) {
		token++;
	}
	return token;
}

char * path_traverse(path_iterator_t * iterator) {
	char * token = path_skip_separators(iterator->token);
	if (*token == 0) {
		return NULL;
	}
	iterator->token = path_next_token(token);
	iterator->token_size = iterator->token - token;
	return token;
}
