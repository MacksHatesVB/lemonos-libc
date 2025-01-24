#include <stdint.h>
#include <stdio.h>
#include <pci.h>

// pci shit because yeah

void pci_config_set_addr(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	uint32_t address = 0x80000000
		| (offset  & 0xf00) << 16
		| (bus  & 0xff)  << 16
		| (slot  & 0x1f)  << 11
		| (function & 0x07)  << 8
		| (offset  & 0xfc);
	outd(0xcf8, address);
}

uint8_t pci_config_inb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	pci_config_set_addr(bus, slot, function, offset);
	return ind(0xcfc) >> ((offset & 2) * 8);
}

uint16_t pci_config_inw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	pci_config_set_addr(bus, slot, function, offset);
	return ind(0xcfc) >> ((offset & 3) * 8);
}


uint32_t pci_config_ind(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	pci_config_set_addr(bus, slot, function, offset);
	return ind(0xcfc);
}

void pci_config_outb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint8_t d) {
	uint32_t new = pci_config_ind(bus, slot, function, offset);
	new |= d << ((offset & 2) * 8);

	pci_config_set_addr(bus, slot, function, offset);
	outd(0xcfc, new);
}

void pci_config_outw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint16_t d) {
	uint32_t new = pci_config_ind(bus, slot, function, offset);
	new |= d << ((offset & 3) * 8);

	pci_config_set_addr(bus, slot, function, offset);
	outd(0xcfc, new);
}

void pci_config_outd(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint32_t d) {
	pci_config_set_addr(bus, slot, function, offset);
	outd(0xcfc, d);
}

void pci_cmd_set_flags(pci_t * device, uint32_t cmd) {
	uint16_t c = pci_config_inw(device->bus, device->slot, device->function, 0x4);
	c |= cmd;
	pci_config_outw(device->bus, device->slot, device->function, 0x4, c);
}
