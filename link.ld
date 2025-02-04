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
		/DISCARD/ : {
			*(.note.*)
			*(.comment .comment.*)
		}
	}
