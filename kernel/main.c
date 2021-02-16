#include "../io/print.h"
#include "../io/io.h"


int main(void)
{
    clear(TEXT);
    enable_cursor();
    cursor_setpos(10, 10);
    print("Hallo Welt", TEXT);
    //print("Hallo Welt", TEXT);
    //print("Hallo Welt", TEXT);
    printat("Hallo Welt", TEXT , 1, 1);
    printat("Hallo Welt", TEXT , 2, 2);
    printat("Hallo Welt", TEXT , 3, 3);
    printat("Hallo Welt", TEXT , 4, 4);
    printat("H_a_l_l_o_ _W_e_l_t_", TEXT_COLOR , 5, 5);
    
    while (1);
}
