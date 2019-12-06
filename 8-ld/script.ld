ENTRY(start)
SECTIONS {
    . = 0x9900000;
    .text : {
        *(.text);
        PROVIDE (_end = .);
    }
    . = 0x6500000;
    .rodata : {
        *(.rodata);
    }
    . = 0x2500000;
    .data : {
        *(.data);
    }
    . = 0x5100000;
    .bss : {
        *(.bss);
    }
}