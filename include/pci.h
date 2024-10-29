#pragma once

#include <stdint.h>

void pci_config_set_addr(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint8_t pci_config_inb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint16_t pci_config_inw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint32_t pci_config_ind(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint32_t pci_config_outb(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint8_t d);
uint32_t pci_config_outw(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint16_t d);
uint32_t pci_config_outd(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint32_t d);

