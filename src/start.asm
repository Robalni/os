        use32

section .text
        global start
        extern kmain
        extern key_pressed

start:
        mov al, 0x10
        out 0x20, al
        mov al, 0x20
        out 0x21, al
        mov al, 0x01
        out 0x21, al
        mov al, 0x00
        out 0x21, al
        mov al, 0xfd
        out 0x21, al
        mov al, 0xff
        out 0xa1, al
        lidt [idt]
        sti

        call kmain
        jmp $

int_handle:
        pop eax
        iret

int_handle_kbd:
        push eax
        mov al, 0x20
        out 0x20, al
        pop eax

        xor al, al
readkbd:
        xor eax, eax
        in al, 0x60
        cmp al, 0
        je readkbd
        push eax
        call key_pressed

        pop eax
        iret

;;; IDT - Interrupt Descriptor Table
;;; Type/attributes bits:
;;;   present, minimum-privilege[2], storage-segment (0 for int gates)
;;;   gate-type[4]
;;; Gate-type:
;;;   0101: 80386 32 bit task gate
;;;   0110: 80286 16-bit interrupt gate
;;;   0111: 80286 16-bit trap gate
;;;   1110: 80386 32-bit interrupt gate
;;;   1111: 80386 32-bit trap gate
idt_start:
        times (0x0d * 8 - ($ - idt_start)) db 0x00
idt_gpf:
        dw int_handle           ; offset 0:15
        dw 0x08                 ; code segment selector
        db 0x00                 ; unused
        db 0b1000_1110          ; type/attributes
        dw 0x0000               ; offset 16:31

        times (0x21 * 8 - ($ - idt_start)) db 0x00
idt_keyboard:
        dw int_handle_kbd       ; offset 0:15
        dw 0x08                 ; code segment selector
        db 0x00                 ; unused
        db 0b1000_1110          ; type/attributes
        dw 0x0000               ; offset 16:31

idt:
        dw (idt - idt_start) - 1
        dd idt_start
