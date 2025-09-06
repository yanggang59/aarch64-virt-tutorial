SECTIONS
{
	. = 0x40100000;
	.text.boot : { 
		*(.text.boot) 
	}
	. = ALIGN(4096);
	.text : { 
		*(.text) 
	}
	.rodata : { 
		*(.rodata) 
	}
	.data : { 
		*(.data) 
	}
	. = ALIGN(4096);
	bss_begin = .;
	.bss : { 
		*(.bss*) 
	} 
	bss_end = .;
}
