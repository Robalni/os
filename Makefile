all: os.img

main.o: src/main.c
	gcc -m32 -c src/main.c

main.elf: main.o start.o
	ld -nostdlib -nodefaultlibs -o main.elf -T link.ld main.o start.o

main.bin: main.elf
	objcopy -O binary main.elf main.bin

os.img: main.bin boot.bin
	cat boot.bin main.bin > os.img

boot.bin: src/boot.asm
	nasm -w+orphan-labels -f bin -o boot.bin src/boot.asm

start.o: src/start.asm
	nasm -w+orphan-labels -f elf32 -o start.o src/start.asm

clean:
	rm -f os *.o *.bin *.elf *.img

run:
	qemu-system-i386 -drive file=os.img,format=raw,if=floppy
