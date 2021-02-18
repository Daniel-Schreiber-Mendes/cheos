#include "terminal.h"


static volatile char *videoadress = 0xb8000;


void tml_init(void)
{
    tml_clear(TEXT);
    tml_cursor_enable();
    tml_cursor_setpos(0, 0);
}


void tml_print(char const *string, PrintMode mode)
{
    uint16_t i=0;
    uint16_t pos = tml_cursor_getpos();
    switch (mode)
    {
        case TEXT:
            while (string[i])
            {
                videoadress[(i + pos) * 2] = string[i];
                ++i;
            }
            tml_cursor_move(i);
            break;
        case TEXT_COLOR:
            while (string[i])
            {
                videoadress[i + pos * 2] = string[i];
                ++i;
            }
            tml_cursor_move(i / 2);
            break;
        case COLOR:
            break;
    }
}


void tml_printc(char c)
{
    videoadress[tml_cursor_getpos() * 2] = c;
    tml_cursor_move(1);
}


void tml_printat(char const *string, PrintMode mode, unsigned char x, unsigned char y)
{
    switch (mode)
    {
        case TEXT:
            for (unsigned short int i=0; string[i] != 0; ++i)
            {
                videoadress[x * 2 + y * CONSOLE_WIDTH + i * 2] = string[i];
            }
            break;
        case TEXT_COLOR:
            for (unsigned short int i=0; string[i] != 0; ++i)
            {
                videoadress[x * 2 + y * CONSOLE_WIDTH + i] = string[i];
            }
            break;
       case COLOR:
            break;
    }
}


void tml_clear(PrintMode mode)
{
    switch (mode)
    {
        case TEXT:
            for (uint16_t i=0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT; ++i)
            {
                videoadress[i * 2] = 0;
            }
            break;
        case TEXT_COLOR:
            for (uint16_t i=0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT; ++i)
            {
                videoadress[i] = 0;
            }
            break;
       case COLOR:
            for (uint16_t i=0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT; ++i)
            {
                videoadress[i * 2 + 1] = 0;
            }
            break;
    }
}


void tml_rmvc(void)
{
    tml_cursor_move(-1);
    tml_printc(' ');
    tml_cursor_move(-1);
}


void tml_cursor_enable(void)
{
    outb(CURSOR_CTRL, CURSOR_SCANLINE_BEGIN_BYTE);
    outb(CURSOR_DATA,  LOWEST_SCANLINE); 
	//outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | 0);
    
	outb(CURSOR_CTRL, CURSOR_SCANLINE_END_BYTE);
	outb(CURSOR_DATA, HIGHEST_SCANLINE); 
	//outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | 15);
}

void tml_cursor_disable(void)
{
	outb(CURSOR_CTRL, CURSOR_ENABLED_BYTE);
	outb(CURSOR_DATA, CURSOR_DISABLE);
}

void tml_cursor_setpos(uint8_t x, uint8_t y)
{
	uint16_t pos = y * CONSOLE_WIDTH + x;
 
	outb(CURSOR_CTRL, CURSOR_L_POS_BYTE);
	outb(CURSOR_DATA, (uint8_t) (pos & 0xFF));
	outb(CURSOR_CTRL, CURSOR_H_POS_BYTE);
	outb(CURSOR_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}


uint16_t tml_cursor_getpos(void)
{
    outb(CURSOR_CTRL, CURSOR_L_POS_BYTE);
    uint16_t pos = inb(CURSOR_DATA);
    outb(CURSOR_CTRL, CURSOR_H_POS_BYTE);
    pos += ((uint16_t)inb(CURSOR_DATA)) << 8;
    return pos; 
}


void tml_cursor_move(int16_t len)
{
    uint16_t pos = tml_cursor_getpos() + len;
    if (pos > CONSOLE_WIDTH * CONSOLE_HEIGHT * 2)
    {
        pos = 0;
    }
	outb(CURSOR_CTRL, CURSOR_L_POS_BYTE);
	outb(CURSOR_DATA, (uint8_t) (pos & 0xFF));
	outb(CURSOR_CTRL, CURSOR_H_POS_BYTE);
	outb(CURSOR_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}


void tml_scroll(void)
{
    for (uint16_t i=0; i < CONSOLE_WIDTH / 2 * CONSOLE_HEIGHT; i++)
    {
        ((uint16_t*)videoadress)[i] = ((uint16_t*)videoadress)[i + CONSOLE_WIDTH / 2];
    }
    tml_cursor_move(-CONSOLE_WIDTH / 2);
}
