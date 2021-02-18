#include "../io/io.h"
#include "../io/keyboard/keyboard.h"
#include "../terminal/terminal.h"

_Noreturn main(void)
{
    tml_init();
    keyb_init();
}
