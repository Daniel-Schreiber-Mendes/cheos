#include "terminal.h"


static volatile C *videoadress = 0xb8000;
static U8 color;


void tml_init(void)
{
    cursor_clear(TEXT);
    cursor_enable();
    cursor_setpos_xy(0, 0);
}


void print(C const *string)
{
    for (U16 i=0; string[i] != 0; ++i)
    {
        printc(string[i]);
    }
}


void printf(C const *string)
{
    for (U16 i=0; string[i] != 0; ++i)
    {
        printc(string[i]);
    }
}


void printr(C const *string, PrintMode mode)
{
    U16 i = 0;
    U16 pos = cursor_getpos();
    switch (mode)
    {
        case TEXT: //write text into memory without affecting color
            while (string[i])
            {
                videoadress[i * 2 + pos * 2] = string[i];
                ++i;
            }
            cursor_move(i);
            break;
        case TEXT_COLOR:
            while (string[i])
            {
                videoadress[i + pos * 2] = string[i];
                ++i;
            }
            cursor_move(i / 2);
            break;
        case COLOR:
            while (string[i])
            {
                videoadress[i * 2 + pos * 2 + 1] = string[i];
                ++i;
            }
            cursor_move(i);
            break;
    }
}


void printc(C c)
{
    if (c == '\n')
    {
        cursor_newline();
    }
    else
    {
        videoadress[cursor_getpos() * 2] = c;
        if (color != 0)
        {
            videoadress[cursor_getpos() * 2 + 1] = color;
        }
        cursor_move(1);
    }
}


void printat(C const *string, U8 x, U8 y)
{
    for (U16 i=0; string[i] != 0; ++i)
    {
        printcat(string[i], x, y);
    }
}


void printfat(C const *string, U8 x, U8 y)
{

}

void printrat(C const *string, PrintMode mode, U8 x, U8 y)
{
    U16 i = 0;
    U16 pos = x + y * CONSOLE_ROW_SIZE;
    switch (mode)
    {
        case TEXT: //write text into memory without affecting color
            while (string[i])
            {
                videoadress[i * 2 + pos * 2] = string[i];
                ++i;
            }
            break;
        case TEXT_COLOR:
            while (string[i])
            {
                videoadress[i + pos] = string[i];
                ++i;
            }
            break;
        case COLOR:
            while (string[i])
            {
                videoadress[i * 2 + pos + 1] = string[i];
                ++i;
            }
            break;
    }
}


void printcat(C c, U8 x, U8 y)
{
    if (c == '\n')
    {
        cursor_newline();
    }
    else
    {
        videoadress[x * 2 + y * CONSOLE_ROW_SIZE * 2] = c;
        if (color != 0)
        {
            videoadress[x * 2 + y * CONSOLE_ROW_SIZE * 2 + 1] = color;
        }
        cursor_move(1);
    }
}


void set_print_color(U8 c)
{
    color = c;
}


void cursor_clear(PrintMode mode)
{
    switch (mode)
    {
        case TEXT:
            for (U16 i=0; i < CONSOLE_ROW_SIZE * CONSOLE_HEIGHT; ++i)
            {
                videoadress[i * 2] = 0;
            }
            break;
        case TEXT_COLOR:
            for (U16 i=0; i < CONSOLE_ROW_SIZE * CONSOLE_HEIGHT; ++i)
            {
                videoadress[i] = 0;
            }
            break;
       case COLOR:
            for (U16 i=0; i < CONSOLE_ROW_SIZE * CONSOLE_HEIGHT; ++i)
            {
                videoadress[i * 2 + 1] = 0;
            }
            break;
    }
}


void cursor_rmvc(void)
{
    cursor_move(-1);
    printc(' ');
    cursor_move(-1);
}


void cursor_newline(void) //line advance
{
    U16 pos = cursor_getpos();
    cursor_setpos(NEXT_MULTIPLE(pos, 80));
}


void cursor_enable(void)
{
    outb(CURSOR_CTRL, CURSOR_SCANLINE_BEGIN_BYTE);
    outb(CURSOR_DATA,  LOWEST_SCANLINE); 
	//outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | 0);
    
	outb(CURSOR_CTRL, CURSOR_SCANLINE_END_BYTE);
	outb(CURSOR_DATA, HIGHEST_SCANLINE); 
	//outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | 15);
}

void cursor_disable(void)
{
	outb(CURSOR_CTRL, CURSOR_ENABLED_BYTE);
	outb(CURSOR_DATA, CURSOR_DISABLE);
}

void cursor_setpos_xy(U8 x, U8 y)
{
    cursor_setpos(y * CONSOLE_ROW_SIZE + x);
}


void cursor_setpos(U16 pos)
{
    if (pos > CONSOLE_WIDTH * CONSOLE_HEIGHT)
    {
        pos = 0;
    }
	outb(CURSOR_CTRL, CURSOR_L_POS_BYTE);
	outb(CURSOR_DATA, (U8) (pos & 0xFF));
	outb(CURSOR_CTRL, CURSOR_H_POS_BYTE);
	outb(CURSOR_DATA, (U8) ((pos >> 8) & 0xFF));
}


U16 cursor_getpos(void)
{
    outb(CURSOR_CTRL, CURSOR_L_POS_BYTE);
    U16 pos = inb(CURSOR_DATA);
    outb(CURSOR_CTRL, CURSOR_H_POS_BYTE);
    pos += ((U16)inb(CURSOR_DATA)) << 8;
    return pos; 
}


void cursor_move(I16 len)
{
    cursor_setpos(cursor_getpos() + len);
}


void cursor_scroll(void)
{
    for (U16 i=0; i < CONSOLE_ROW_SIZE / 2 * CONSOLE_HEIGHT; i++)
    {
        ((U16*)videoadress)[i] = ((U16*)videoadress)[i + CONSOLE_ROW_SIZE / 2];
    }
    cursor_move(-CONSOLE_ROW_SIZE / 2);
}
