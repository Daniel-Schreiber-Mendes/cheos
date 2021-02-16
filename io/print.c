#include "print.h"

volatile char *videoadress = 0xb8000;


void print(char const *string, PrintMode mode)
{
    uint16_t offset = 0;
    
    unsigned short int i=0;
    switch (mode)
    {
        case TEXT:
            while (string[i])
            {
                videoadress[(i + offset) * 2] = string[i];
                ++i;
            }
            break;
        case TEXT_COLOR:
            while (string[i])
            {
                videoadress[i + offset * 2] = string[i];
                ++i;
            }
            break;
        case COLOR:
            break;
    }
}


void printat(char const *string, PrintMode mode, unsigned char x, unsigned char y)
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


void clear(PrintMode mode)
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
