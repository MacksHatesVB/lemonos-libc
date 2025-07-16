OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS
	{
		.text : {
			. = ALIGN(8);
			*(.text .text.*)
		}
		.rodata : {
			*(.rodata .rodata.*)
		}
		.data : {
			*(.data .data.*)
			*(.bss .bss.*)
			*(COMMON)
		}
		.reloc : {
			*(.reloc .reloc.*)
		}
		.rel : {
			__relsym = .;
			*(.rel .rel.*)
			__relsym_end = .;
		}
		.interp : {
			*(.interp .interp.*)
		}
		.plt : {
			*(.plt .plt.*)
		}
		.got : {
			*(.got .got.*)
		}
		/DISCARD/ : {
			*(.comment .comment.*)
		}
	}
