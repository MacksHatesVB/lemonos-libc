OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS
        {
                .text : {
                                . = ALIGN(8);
                                *(.text)
                        }
                .data :{ *(.data) }
                .bss : { *(.bss) }
        }
