#include <io.h>
#include <keyboard.h>
#include <terminal.h>
#include <string.h>
#include <pages.h>
#include <multiboot.h>


_Noreturn main(multiboot_info_t *mbi, U32 magic)
{
    tml_init();
	pages_init(mbi, magic);
	keyb_init();
}


