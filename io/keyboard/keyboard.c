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
KEY_SHIFT_R = 0,
KEY_AE = 0,
KEY_OE = 0,
KEY_UE = 0,
KEY_ESC = 0,
KEY_ESZETT = 0,
KEY_NULL_KEY = 0,
KEY_CRTL = 0,
KEY_ARROW_L = 0,
KEY_ARROW_R = 0,
KEY_ARROW_U = 0,
KEY_ARROW_D = 0,
KEY_POS1 = 0,
KEY_PICT_U = 0,
KEY_PICT_D = 0,
KEY_END = 0,
KEY_REMOVE = 0,
KEY_INSERT = 0,
KEY_PAUSE = 0,
KEY_SCROLL = 0,
KEY_ENTER = 0,
KEY_CAPSLOG = 0,
KEY_UNKNOWN = 0,
KEY_F1 = 0, 
KEY_F2 = 0, 
KEY_F3 = 0, 
KEY_F4 = 0, 
KEY_F5 = 0, 
KEY_F6 = 0, 
KEY_F7 = 0, 
KEY_F8 = 0, 
KEY_F9 = 0, 
KEY_F10 = 0,
KEY_FORWARD_TICKS = 0,
KEY_BACK_TICKS = 0,
KEY_SECTION_SIGN = 0,
KEY_PERCENT = 0,
KEY_SHIFT_L = 43,
KEY_SHIFT_L_RELEASED = 66,
KEY_ALTGR = 57,
KEY_ALTGR_RELEASED_1 = 0x66,
KEY_ALTGR_RELEASED_2 = 0x64
};

enum RKEYS
{
    RKEY_MODIFIER = 0x00E0,
    RKEY_ALTGR = 0x0038,
    RKEY_ALTGR_RELEASED = 0x00B8,
    RKEY_SHIFT_L = 0x002A,
    RKEY_SHIFT_L_RELEASED = 0x00AA,
    RKEY_REMOVE = 14,
    RKEY_ENTER = 28
};


static C charset[] =
{
  KEY_NULL_KEY, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', KEY_ESZETT, KEY_FORWARD_TICKS,'\b',
  '\t','q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', KEY_UE, '+',
  '\n', KEY_CRTL, 'a', 's','d', 'f', 'g', 'h', 'j', 'k', 'l', KEY_OE, KEY_AE, KEY_UNKNOWN, KEY_SHIFT_L,  
  '#', 'y', 'x', 'c', 'v','b', 'n', 'm', ',', '.', '-',   KEY_SHIFT_R, 
  '?', KEY_ALTGR, ' ', KEY_CAPSLOG, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_PAUSE, KEY_SCROLL, KEY_POS1, KEY_ARROW_U, KEY_PICT_U, KEY_UNKNOWN, KEY_ARROW_L, KEY_UNKNOWN, KEY_ARROW_R, KEY_UNKNOWN, KEY_END, KEY_ARROW_D, KEY_PICT_D, KEY_INSERT, KEY_REMOVE
};

static C charset_shift[] =
{
  KEY_NULL_KEY, KEY_ESC, '!', '"', KEY_SECTION_SIGN, KEY_PERCENT, '%', '&', '/', '(', ')', '=', '?', KEY_BACK_TICKS,'\b',
  '\t','Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', KEY_UE, '*',
  '\n', KEY_CRTL, 'A', 'S','D', 'F', 'G', 'H', 'J', 'K', 'L', KEY_OE, KEY_AE, KEY_UNKNOWN, KEY_SHIFT_L,  
  '\'', 'Y', 'X', 'C', 'V','B', 'N', 'M', ';', ':', '_',   KEY_SHIFT_R, 
  KEY_UNKNOWN, KEY_ALTGR, ' ', KEY_CAPSLOG, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_PAUSE, KEY_SCROLL, KEY_POS1, KEY_ARROW_U, KEY_PICT_U, KEY_UNKNOWN, KEY_ARROW_L, KEY_UNKNOWN, KEY_ARROW_R, KEY_UNKNOWN, KEY_END, KEY_ARROW_D, KEY_PICT_D, KEY_INSERT, KEY_REMOVE
};


static C charset_altgr[] =
{
  KEY_NULL_KEY, KEY_ESC, '1', '2', '3', '4', '5', '6', '{', '[', ']', '}', '\\', KEY_FORWARD_TICKS,'\b',
  '\t','q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', KEY_UE, '~',
  '\n', KEY_CRTL, 'a', 's','d', 'f', 'g', 'h', 'j', 'k', 'l', KEY_OE, KEY_AE, KEY_UNKNOWN, KEY_SHIFT_L,  
  '#', 'y', 'x', 'c', 'v','b', 'n', 'm', ',', '.', '-',   KEY_SHIFT_R, 
  '?', KEY_ALTGR, ' ', KEY_CAPSLOG, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_PAUSE, KEY_SCROLL, KEY_POS1, KEY_ARROW_U, KEY_PICT_U, KEY_UNKNOWN, KEY_ARROW_L, KEY_UNKNOWN, KEY_ARROW_R, KEY_UNKNOWN, KEY_END, KEY_ARROW_D, KEY_PICT_D, KEY_INSERT, KEY_REMOVE
};


static C modkey;


void keyb_init(void)
{
    keyb_listener();
}


void keyb_listener(void)
{
    while (1)
    {
        C rawc = keyb_getc_raw();
        if (rawc != KEYB_NO_INPUT)
        {
            if (rawc == RKEY_MODIFIER) //means next key is going to be modifer key
            {
                modkey = RKEY_MODIFIER;
                continue;
            }
            if (modkey == RKEY_MODIFIER) //if last key was key that indicated next key is going to be modifier key
            {
                switch (rawc)
                {
                    case RKEY_ALTGR:
                        modkey = RKEY_ALTGR;
                        break;
                    case RKEY_ALTGR_RELEASED:
                        modkey = 0;
                        break;   
                    case RKEY_SHIFT_L:
                        modkey = RKEY_SHIFT_L;
                        break;
                    case RKEY_SHIFT_L_RELEASED:
                        modkey = 0;
                        break;
                }
                continue;
            }

            switch (rawc)
            {
                case RKEY_REMOVE:
                    cursor_rmvc();
                    break;
                case RKEY_ENTER:
                    cursor_newline();
                    break;
                case RKEY_SHIFT_L:
                    modkey = RKEY_SHIFT_L;
                    break;
                case RKEY_SHIFT_L_RELEASED:
                    modkey = 0;
                    break;
                default:
                    if (rawc < 96)
                    {
                        switch (modkey)
                        {
                            case RKEY_SHIFT_L:
                                printc(charset_shift[rawc]);
                                break;
                            case RKEY_ALTGR:
                                printc(charset_altgr[rawc]);
                                break;
                            default: //modkey is 0
                                printc(charset[rawc]);
                                break;
                        }
                    }
            } 
                
        }
    }
}


C keyb_read_raw(void)
{
    C c;
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


C keyb_getc_raw(void)
{
    while (!(inb(KEYB_SR) & KEYB_EVENT_FLG)) //wait for input
        ;
    return inb(KEYB_DR); 
}


void set_leds(void)
{
    send_command(KEYB_CAPSLLED_ENABLE);
}


void send_command(U8 cmd)
{
	while (inb (KEYB_SR) & KEYB_CONTROLER_READY_FLG) ;
	outb (KEYB_DR, cmd);
}
