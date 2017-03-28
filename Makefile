all: os.img

start.o: src/start.asm
	nasm -w+orphan-labels -f elf32 -o start.o src/start.asm

main.o: src/main.c
	gcc -m32 -ffreestanding -c src/main.c

keyboard.o: src/keyboard.c
	gcc -m32 -ffreestanding -c src/keyboard.c

os.elf: main.o start.o keyboard.o
	ld -nostdlib -o os.elf -T link.ld start.o main.o keyboard.o

os.bin: os.elf
	objcopy -O binary os.elf os.bin

os.img: boot.bin os.bin
	cat boot.bin os.bin > os.img

boot.bin: src/boot.asm
	nasm -w+orphan-labels -f bin -o boot.bin src/boot.asm

clean:
	rm -f os *.o *.bin *.elf *.img

run:
	qemu-system-i386 -drive file=os.img,format=raw,if=floppy
