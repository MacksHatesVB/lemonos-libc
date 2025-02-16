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
			*(.rel .rel.*)
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
