#ifndef IO_H
#define IO_H
#include "../kernel/types.h"


#define CONSOLE_WIDTH 160
#define CONSOLE_HEIGHT 25
#define CURSOR_CTRL 0x3D4
#define CURSOR_DATA 0x3D5


void enable_cursor(void);
void disable_cursor(void);
void cursor_setpos(uint8_t x, uint8_t y);
void move_cursor(uint8_t dx, uint8_t dy);

#endif
