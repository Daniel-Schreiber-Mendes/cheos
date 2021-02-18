#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../io.h"
#include "../../terminal/terminal.h"

typedef unsigned char uchar;

void keyb_init(void);
void keyb_listener(void);
void keyb_custom_codes_set(void);
uchar keyb_read_raw(void); //directly get char
uchar keyb_getc_raw(void); //wait for char
void set_leds(void);
void send_command(uint8_t cmd);

#endif
