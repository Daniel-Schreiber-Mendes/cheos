#ifndef MALLOC_H
#define MALLOC_H

#include <types.h>
#include <io.h>
#include <string.h>
#include <terminal.h>

void mmap_init(void);
void* malloc(U16 size);
void free(void *ptr);

#endif