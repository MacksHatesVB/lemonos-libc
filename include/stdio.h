#pragma once

#include <stdint.h>

int open(char * name, int flags);
ssize_t write(int fd, const void * buf, size_t count);
ssize_t read(int fd, void * buf, size_t count);
int close(int fd);
void puts(char * text);
void printf(char * fmt, ...);
void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, long val);
void outd(uint16_t port, uint32_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
long inl(uint16_t port);
uint32_t ind(uint16_t port);
