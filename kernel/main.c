#include <io.h>
#include <keyboard.h>
#include <terminal.h>
#include <string.h>
#include <malloc.h>
#include "multiboot.h"


_Noreturn main(multiboot_info_t *mbi, U32 magic)
{
    tml_init();
    set_print_color(2);
    print("Terminal initialized\n");


	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		set_print_color(4);
		print("Bootloader args are not correct\n");
		set_print_color(2);
	}

	mmap_init();
	print("Memory Map initialized\n");

    for (U8 i=0; i < 10; ++i)
    {
		C str[17];
		str[16] = 0;
		i32toha(((memory_map_t*)(mbi->mmap_addr) + i)->type, str);
    }

    keyb_init();
}

