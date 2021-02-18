#ifndef IO_H
#define IO_H
#include "../kernel/types.h"

extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);

#endif
