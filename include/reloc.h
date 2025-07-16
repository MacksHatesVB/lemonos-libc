#pragma once

#include <stdint.h>

typedef struct {
	uint32_t offset;
	uint16_t info;
} elf_rel32_t;

typedef struct {
	uint32_t offset;
	uint16_t info;
	int32_t addend;
} elf_rela32_t;

typedef struct {
	uint64_t offset;
	uint64_t info;
} elf_rel64_t;

typedef struct {
	uint64_t offset;
	uint64_t info;
	int64_t addend;
} elf_rela64_t;

enum {
	REL_NONE = 0x00,
	REL_EIP_REL = 0x01,
	REL_ADDITIVE = 0x02,
	REL_GOT = 0x03,
	REL_PLT = 0x04,
	REL_COPY = 0x05,
	REL_GLOB = 0x06,
	REL_JMP = 0x07,
	REL_REL = 0x08,
	REL_OFF_GOT = 0x09,
	REL_EIP_GOT = 0x0a,
	REL_PLT32 = 0x0b,
	REL_16 = 0x14,
	REL_EIP_16 = 0x15,
	REL_8 = 0x16,
	REL_EIP_8 = 0x17,
	REL_SIZE = 0x26,
};

void __reloc_setup();
extern uint32_t __reloc_get_reference_offset();
extern uint32_t __reloc_get_reference_vaddr();
extern uint32_t __reloc_get_base_vaddr();
