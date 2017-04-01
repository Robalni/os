all: os.img

start.o: src/start.asm
	nasm -w+orphan-labels -f elf32 -o start.o src/start.asm

main.o: src/main.c src/shell.h src/keyboard.h src/console.h
	gcc -m32 -ffreestanding -c src/main.c

keyboard.o: src/keyboard.c src/keyboard.h
	gcc -m32 -ffreestanding -c src/keyboard.c

console.o: src/console.c src/console.h
	gcc -m32 -ffreestanding -c src/console.c

shell.o: src/shell.c src/shell.h src/console.h
	gcc -m32 -ffreestanding -c src/shell.c

os.elf: main.o start.o keyboard.o console.o shell.o
	ld -nostdlib -o os.elf -T link.ld start.o main.o keyboard.o console.o shell.o

os.bin: os.elf
	objcopy -O binary os.elf os.bin

os.img: boot.bin os.bin
	cat boot.bin os.bin > os.img

boot.bin: src/boot.asm
	nasm -w+orphan-labels -f bin -o boot.bin src/boot.asm

clean:
	rm -f os *.o *.bin *.elf *.img

run: os.img
	qemu-system-i386 -drive file=os.img,format=raw,if=floppy
