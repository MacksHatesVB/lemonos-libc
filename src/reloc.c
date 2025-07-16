#include <reloc.h>

extern elf_rel32_t __relsym;
extern elf_rel32_t __relsym_end;

void __reloc_process(uint32_t vm_base, elf_rel32_t * relocation) {
	uint8_t type = relocation->info & 0xff;
	uint32_t * p = (uint32_t *) (vm_base + relocation->offset);
	switch (type) {
		case REL_REL:
			*p += vm_base;
			break;
	}
}

void __reloc_setup() {
	uint32_t vm_base = __reloc_get_base_vaddr();

	elf_rel32_t * relsyms = &__relsym;
	elf_rel32_t * relsyms_end = &__relsym_end;
	while ((uint32_t) relsyms != (uint32_t) relsyms_end) {
		__reloc_process(vm_base, relsyms++);
	}
}
