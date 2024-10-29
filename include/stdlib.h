#pragma once

#include <stdint.h>
#include <stddef.h>

void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, long val);
void outd(uint16_t port, uint32_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
long inl(uint16_t port);
uint32_t ind(uint16_t port);
int cpu_get_temp();
void exit(int status);
int syscall(const int number, ...);
void * malloc(size_t size);
void free(void * p);
