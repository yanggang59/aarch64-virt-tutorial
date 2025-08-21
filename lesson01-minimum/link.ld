SECTIONS
{
    . = 0x40100000;
    .text : { *(.text.boot) }

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}