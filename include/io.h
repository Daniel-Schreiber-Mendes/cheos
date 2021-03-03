#ifndef IO_H
#define IO_H
#include <types.h>

extern void outb(U16 port, U8 val);
extern U8 inb(U16 port);

#endif
