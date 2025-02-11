#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <tar.h>
#include <sys/stat.h>

uint32_t tar_size(char * in, int length) {
	uint32_t size = 0;
	uint32_t count = 1;
	for (uint32_t j = length - 1; j > 0; j--, count *= 8) {
		size += ((in[j - 1] - '0') * count);
	}
	return size;
}

int tar_extract_file(tar_header_t * header, size_t size) {
	void * data = header;
	data += 512;

	FILE * fp = fopen(header->filename, "w");
	fwrite(data, size, 1, fp);
	fclose(fp);
}

int tar_extract_dirent(tar_header_t * header, size_t size) {
	mkdir(header->filename, tar_size(header->mode, 8));
}

int tar_extract(tar_handlers_t * handlers, void * contents, size_t size) {
	tar_header_t * header = contents;
	tar_header_t * end = contents + size;
	tar_callback_t file = handlers->file;
	tar_callback_t dirent = handlers->dirent;
	while ((*header->filename != 0) && (header < end)) {
		size = tar_size(header->size, 12);
		switch (header->type) {
			default:
				return 1;
			case '0':
			case '\0':
				if (file(header, size)) {
					return 1;
				}
				break;
			case '5':
				if (dirent(header, size)) {
					return 1;
				}
				break;
		}

		contents += ((size / 512) + 1) * 512;
		if (size % 512) {
			contents += 512;
		}
		header = contents;
	}
	return 0;
}
