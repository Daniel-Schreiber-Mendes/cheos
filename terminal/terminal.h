#ifndef SHELL_H
#define SHELL_H

#include "../io/io.h"

#define CONSOLE_WIDTH 160 //(1 char + 1 color) * 80
#define CONSOLE_HEIGHT 25
#define CURSOR_CTRL 0x3D4
#define CURSOR_DATA 0x3D5
#define CURSOR_L_POS_BYTE 0x0F
#define CURSOR_H_POS_BYTE 0x0E
#define CURSOR_SCANLINE_BEGIN_BYTE 0x0A /* there are 16 scanlines */
#define CURSOR_SCANLINE_END_BYTE 0x0B
#define LOWEST_SCANLINE 0
#define HIGHEST_SCANLINE 15
#define CURSOR_ENABLED_BYTE 0x0A
#define CURSOR_DISABLE 0x20

typedef enum
{
    TEXT,
    COLOR,
    TEXT_COLOR
}
PrintMode;

void     tml_init(void);
void     tml_print(char const *string, PrintMode mode);
void     tml_printc(char c);
void     tml_printat(char const *string, PrintMode mode, unsigned char x, unsigned char y); 
void     tml_clear(PrintMode mode);
void     tml_rmvc(void);

void     tml_cursor_enable(void);
void     tml_cursor_disable(void);
void     tml_cursor_setpos(uint8_t x, uint8_t y);
uint16_t tml_cursor_getpos(void);
void     tml_cursor_move(int16_t len);
void     tml_scroll(void);


#endif
