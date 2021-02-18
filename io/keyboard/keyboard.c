#include "keyboard.h"

#define KEYB_DR 0x60 //data register
#define KEYB_SR 0x64 //status register
#define KEYB_NO_INPUT 0
#define KEYB_EVENT_FLG 0x01
#define KEYB_CONTROLER_READY_FLG 0x02
//commands
#define KEYB_CAPSLLED_ENABLE 0x04


enum KEYS
{
KEY_SHIFT_L = 0,
KEY_SHIFT_R = 0,
KEY_INSERT = 0,
KEY_AE = 0,
KEY_OE = 0,
KEY_UE = 0,
KEY_ESC = 0,
KEY_ESZETT = 0,
KEY_NULL_KEY = 0,
KEY_CRTL = 0,
KEY_ALTGR = 0,
KEY_ARROW_L = 0,
KEY_ARROW_R = 0,
KEY_ARROW_U = 0,
KEY_ARROW_D = 0,
};


static uchar charset[255] =
{
  KEY_NULL_KEY, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', KEY_ESZETT, '`','\b',
  '\t','q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', KEY_UE, '+',
  '\n', KEY_CRTL, 'a', 's','d', 'f', 'g', 'h', 'j', 'k', 'l', KEY_OE, KEY_AE , KEY_INSERT, KEY_SHIFT_L,  
  '#', 'y', 'x', 'c', 'v','b', 'n', 'm', ',', '.', '-',   KEY_SHIFT_R, 
  '?', KEY_ALTGR, ' ', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'O', 'P', KEY_ARROW_U, 'R', 'S', KEY_ARROW_L, 'U', KEY_ARROW_R, 'W', 'D', KEY_ARROW_D, 'D', 'D', 'D'
};


void keyb_init(void)
{
    keyb_listener();
}


void keyb_listener(void)
{
    while (1)
    {
        uchar c = charset[keyb_getc_raw()];
        if (c != KEYB_NO_INPUT)
        {
            switch (c)
            {
                case '\b':
                    tml_rmvc();
                    break;
                default:
                    if (c < 128)
                        tml_printc(c);
            } 
                
        }
    }
}


uchar keyb_read_raw(void)
{
    uchar c;
    if (inb(KEYB_SR) & KEYB_EVENT_FLG)
    {
        c = inb(KEYB_DR); 
    }
    else
    {
        c = KEYB_NO_INPUT;
    }
    return c;
}


uchar keyb_getc_raw(void)
{
    while (!(inb(KEYB_SR) & KEYB_EVENT_FLG)) //wait for input
        ;
    return inb(KEYB_DR); 
}


void set_leds(void)
{
    send_command(KEYB_CAPSLLED_ENABLE);
}


void send_command(uint8_t cmd)
{
	while (inb (KEYB_SR) & KEYB_CONTROLER_READY_FLG) ;
	outb (KEYB_DR, cmd);
}
