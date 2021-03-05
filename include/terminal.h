#ifndef SHELL_H
#define SHELL_H

#include <io.h>

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25
#define CONSOLE_ROW_SIZE 160 //(1 uchar + 1 color) * 80
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
#define NEXT_MULTIPLE(x, n) ((x % n == 0) ? x + n : ((x + n - 1) / n * n))

typedef enum
{
    TEXT, //only tex
    COLOR, //only color
    TEXT_COLOR //different color for each char
}
PrintMode;

void print(C const *string);
void printf(C const *string); 
void printr(C const *string, PrintMode mode);
void printc(C c);

//print*at functions dont move the cursor
void printat(C const *string, U8 x, U8 y);
void printfat(C const *string, U8 x, U8 y);
void printrat(C const *string, PrintMode mode, U8 x, U8 y);
void printcat(C c, U8 x, U8 y);

void set_print_color(U8 c);

void tml_init(void);
void cursor_clear(PrintMode mode);
void cursor_rmvc(void);
void cursor_newline(void);
void cursor_enable(void);
void cursor_disable(void);
void cursor_setpos_xy(U8 x, U8 y);
void cursor_setpos(U16 pos);
U16  cursor_getpos(void);
U16  cursor_getposr(void);
void cursor_move(I16 len);
void cursor_scroll(void);


#endif
