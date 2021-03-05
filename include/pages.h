#ifndef PAGES_H
#define PAGES_H

#include <types.h>
#include <io.h>
#include <string.h>
#include <terminal.h>
#include <multiboot.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

struct Page
{
	struct Page *prev, *next;
	U32 len;
	B isFree;
};
typedef struct Page Page;


V pages_init(multiboot_info_t *mbi, U32 magic);
V* malloc(U32 size);
V free(V *addr);

#endif