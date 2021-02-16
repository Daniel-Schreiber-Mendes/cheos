#include "io.h"

extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);

void enable_cursor(void)
{
    outb(CURSOR_CTRL, 0x0A);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | 0); //begin of cursor
	outb(CURSOR_CTRL, 0x0B);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | 16); //end of cursor (vertically)
}

void disable_cursor(void)
{
	outb(CURSOR_CTRL, 0x0A);
	outb(CURSOR_DATA, 0x20);
}

void cursor_setpos(uint8_t x, uint8_t y)
{
	uint16_t pos = y * CONSOLE_WIDTH + x;
 
	outb(CURSOR_CTRL, 0x0F);
	outb(CURSOR_DATA, (uint8_t) (pos & 0xFF));
	outb(CURSOR_CTRL, 0x0E);
	outb(CURSOR_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}

void move_cursor(uint8_t dx, uint8_t dy)
{

}
