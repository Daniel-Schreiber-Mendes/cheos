.POSIX:
.PHONY: clean run

asm_src_files := $(shell find . -name '*.asm')
asm_obj_files := $(asm_src_files:.asm=.o)

c_src_files := $(shell find . -name '*.c')
c_obj_files := $(c_src_files:.c=.o)

cheos.iso: cheos.elf
	cp '$<' iso/boot
	grub-mkrescue -o '$@' iso

# cheos.elf is the multiboot file.
cheos.elf: $(asm_obj_files) $(c_obj_files)
	ld -m elf_i386 -nostdlib -T linker.ld -o '$@' $^
%.o : %.asm
	nasm -f elf32 '$<' -o '$@'
	
%.o : %.c
	gcc -c -m32 -ffreestanding -fno-builtin -Os -o '$@' -Wno-int-conversion -Wall -Wextra -Wno-pointer-sign '$<' -Iinclude
	
clean:
	rm -f *.elf *.o iso/boot/*.elf *.img *.iso

run: cheos.iso
	qemu-system-i386 -hda '$<'
	
run-kernel: cheos.iso
	qemu-system-i386 '$<'
