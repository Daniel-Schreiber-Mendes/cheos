#include "malloc.h"


static void *base_mem_ptr, *free_mem_ptr; 


void mmap_init(void)
{
	base_mem_ptr = 0x00;
    free_mem_ptr = base_mem_ptr;
}


void* malloc(U16 size)
{
	free_mem_ptr += size;
	return free;
}


void free(void *ptr)
{

}