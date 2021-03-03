#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <io.h>
#include <terminal.h>
#include <string.h>

void keyb_init(void);
void keyb_listener(void);
void keyb_custom_codes_set(void);
C keyb_read_raw(void); //directly get char
C keyb_getc_raw(void); //wait for char
void set_leds(void);
void send_command(U8 cmd);

#endif
