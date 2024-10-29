#include <stdint.h>
#include <stdlib.h>

// pci shit because yeah

void pci_config_set_addr(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	uint32_t address = 0x80000000
		| (offset  & 0xf00) << 16
		| (bus  & 0xff)  << 16
		| (slot  & 0x1f)  << 11
		| (function & 0x07)  << 8
		| (offset  & 0xfc);
	outl(0xcf8, address);
}

uint8_t pci_config_inb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	pci_config_set_addr(bus, slot, function, offset);
	return inl(0xcfc + (offset & 2));
}

uint16_t pci_config_inw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	pci_config_set_addr(bus, slot, function, offset);
	return inl(0xcfc + (offset & 3));
}


uint32_t pci_config_ind(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	pci_config_set_addr(bus, slot, function, offset);
	return inl(0xcfc);
}

uint32_t pci_config_outb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint8_t d) {
	pci_config_set_addr(bus, slot, function, offset);
	outl(0xcfc + (offset & 2), d);
}

uint32_t pci_config_outw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint16_t d) {
	pci_config_set_addr(bus, slot, function, offset);
	outl(0xcfc + (offset & 3), d);
}

uint32_t pci_config_outd(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint32_t d) {
	pci_config_set_addr(bus, slot, function, offset);
	outl(0xcfc, d);
}
