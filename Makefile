.POSIX:
.PHONY: clean run rub-img

main.img: main.elf
	cp '$<' iso/boot
	grub-mkrescue -o '$@' iso

# main.elf is the the multiboot file.
main.elf: entry.o main.o
	ld -m elf_i386 -nostdlib -T linker.ld -o '$@' $^

entry.o: entry.asm
	nasm -f elf32 '$<' -o '$@'

main.o: main.asm
	nasm -f elf32 '$<' -o '$@'

clean:
	rm -f *.elf *.o iso/boot/*.elf *.img

run: main.elf
	qemu-system-i386 -kernel '$<'

run-img: main.img
	qemu-system-i386 -hda '$<'
