#include "pages.h"

static Page* get_last_page(Page *page);
static V merge_pages(Page *first, Page *second);
static V print_page_info(Page *page);


static Page *first_page;


V pages_init(multiboot_info_t *mbi, U32 magic)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		set_print_color(4);
		print("Bootloader args are not correct\n");
		set_print_color(2);
		return;
	}

    if (!CHECK_FLAG(mbi->flags, 6))
    {
    	set_print_color(4);
		print("No multiboot memory info available\n");
		set_print_color(2);
		return;
    }

	print("Initializing Pages\n");

    for (multiboot_memory_map_t *mmap = mbi->mmap_addr; (U32)mmap < mbi->mmap_addr + mbi->mmap_length; mmap = ((U32) mmap + mmap->size + sizeof mmap->size))
    {		
		if (mmap->type == 1) //usable ram
		{
			Page *page = mmap->addr;
			if (first_page == 0)
			{
				if (mmap->addr == 0) //in case a page starts at 0, advance one byte, so we dont ever use byte 0
				{
					page = (U32)page + 1;
				}
				first_page = page;
				page->prev = NULL;
			}
			else
			{
				Page *last_page = get_last_page(first_page);
				last_page->next = page;
				page->prev = last_page;
			}
			page->len = mmap->len;
			page->next = NULL;
			page->isFree = 1;

			C str[10];
			str[9] = 0;
			str[8] = ' ';
			print("  Found Page of size ");
	    	i32toha(page->len, str);
			print(str);
			print("at location ");
	    	i32toha(page, str);
			print(str);
			printc('\n');
		}
    }

	print("Pages initialized\n");
}


V* malloc(U32 size)
{
	C s[10];
	s[9] = 0;
	s[8] = '\n';
	print("Requested size: ");
	i32toha(size, s);
	print(s);
	
	for (Page *page = first_page; page; page = page->next)
	{
		print_page_info(page);
		if (page->len >= size && page->isFree)
		{
			Page *new_page = (U32)page + sizeof(Page) + size;
			new_page->len = page->len - (sizeof(Page) + size);
			new_page->next = page->next;
			new_page->prev = page;
			new_page->isFree = 1;

			page->next = new_page;
			page->isFree = 0;
			page->len = size;
			return page + 1;
		}
	}

	C str[9];
	str[8] = 0;
	set_print_color(4);
	print("Malloc: requested size ");
	i32toha(size, str);
	print(str);
	print(" too big\n");
	set_print_color(2);
	return NULL;
}


V free(V *addr)
{
	Page *page = (Page*)addr - 1;
	page->isFree = 1;
	if (page->prev && page->prev->isFree)
	{
		if (page->next && page->next->isFree)
		{
			merge_pages(page->prev, page);
			merge_pages(page->prev, page->next);
		}
		else
		{
			merge_pages(page->prev, page);
		}
	}
	else if (page->next && page->next->isFree)
	{
		merge_pages(page, page->next);
	}
}


static Page* get_last_page(Page *page)
{
	while (page->next)
	{
		page = page->next;
	}
	return page;
}


static V merge_pages(Page *first, Page *second)
{
	first->next = second->next;
	first->len += second->len + sizeof(Page);
}


static V print_page_info(Page *page)
{
	C str[9];
	str[8] = 0;
	print("Page Info:");
	if (page->isFree)
		print("F ");
	else
		print("U ");
	print("Location: ");
	i32toha(page, str);
	print(str);
	print(" Size: ");
	i32toha(page->len, str);
	print(str);
	print(" Prev: ");
	i32toha(page->prev, str);
	print(str);
	print(" Next: ");
	i32toha(page->next, str);
	print(str);
	printc('\n');
}