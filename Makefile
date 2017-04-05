CC = gcc
override CFLAGS := -m32 -ffreestanding -Wall -Wextra -O2 $(CFLAGS)

all: os.img

start.o: src/start.asm
	nasm -w+orphan-labels -f elf32 -o $@ $<

main.o: src/main.c src/shell.h src/keyboard.h src/console.h src/winman.c
	$(CC) $(CFLAGS) -c $<

graphics.o: src/graphics.c src/graphics.h
	$(CC) $(CFLAGS) -c $<

keyboard.o: src/keyboard.c src/keyboard.h
	$(CC) $(CFLAGS) -c $<

console.o: src/console.c src/console.h
	$(CC) $(CFLAGS) -c $<

shell.o: src/shell.c src/shell.h src/keyboard.h src/console.h
	$(CC) $(CFLAGS) -c $<

winman.o: src/winman.c src/winman.h src/graphics.h
	$(CC) $(CFLAGS) -c $<

os.elf: start.o main.o graphics.o keyboard.o console.o shell.o winman.o
	ld -nostdlib -o $@ -T link.ld $^

os.bin: os.elf
	objcopy -O binary $< $@

os.img: boot.bin os.bin
	cat $^ > $@

boot.bin: src/boot.asm
	nasm -w+orphan-labels -f bin -o $@ $<

.PHONY: clean
clean:
	rm -f os *.o *.bin *.elf *.img

run: os.img
	qemu-system-i386 -drive file=$<,format=raw,if=floppy
