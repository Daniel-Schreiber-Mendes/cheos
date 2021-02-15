.POSIX:
.PHONY: clean run

asm_src_files := $(shell find . -name '*.asm')
asm_obj_files := $(asm_src_files:.asm=.o)

c_src_files := $(shell find . -name '*.c')
c_obj_files := $(c_src_files:.c=.o)

main.img: main.elf
	cp '$<' iso/boot
	grub-mkrescue -o '$@' iso

# main.elf is the multiboot file.
main.elf: $(asm_obj_files) $(c_obj_files)
	ld -m elf_i386 -nostdlib -T linker.ld -o '$@' $^
	
%.o : %.asm
	nasm -f elf32 '$<' -o '$@'
	
%.o : %.c
	gcc -c -m32 -std=c99 -ffreestanding -fno-builtin -Os -o '$@' -Wall -Wextra '$<'
	
clean:
	rm -f *.elf *.o iso/boot/*.elf *.img

run: main.img
	qemu-system-i386 -hda '$<'
