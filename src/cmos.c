#include <cmos.h>
#include <stdint.h>
#include <stdio.h>

int cmos_updating() {
	return (cmos_read_register(CMOS_STATUS_A) >> 7) & 1;
}

uint8_t cmos_read_register(uint16_t reg) {
	outb(CMOS_PORT_ADDR, reg);
	return inb(CMOS_PORT_DATA);
}

void cmos_write_register(uint16_t reg, uint8_t value) {
	outb(CMOS_PORT_ADDR, reg);
	outb(CMOS_PORT_DATA, value); // i think
}
