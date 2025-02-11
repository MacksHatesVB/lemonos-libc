#pragma once

#include <stdint.h>
#include <stddef.h>

typedef int FILE; // hate this

FILE * fopen(const char * pathname, const char * mode);
size_t fread(void * ptr, size_t size, size_t nmemb, FILE * stream);
size_t fwrite(void * ptr, size_t size, size_t nmemb, FILE * stream);
int fclose(FILE * stream);
void puts(char * text);
void putchar(char chr);
void printf(char * fmt, ...);
void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, long val);
void outd(uint16_t port, uint32_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
long inl(uint16_t port);
uint32_t ind(uint16_t port);
