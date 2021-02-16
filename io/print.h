#ifndef PRINT_H
#define PRINT_H


#define CONSOLE_WIDTH 160
#define CONSOLE_HEIGHT 25
#define CONSOLE_CTRL 0x3D4
#define CONSOLE_DATA 0x3D5


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;


typedef enum
{
    TEXT,
    COLOR,
    TEXT_COLOR
}
PrintMode;


void print(char const *string, PrintMode mode);
void printat(char const *string, PrintMode mode, unsigned char x, unsigned char y); //doesnt effect cursor
void clear(PrintMode mode);

#endif
