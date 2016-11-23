        use16

        org 0x7c00
        jmp bootloader

bootloader:
        ;; Stack
        mov ax, 0x7bff
        mov sp, ax

        mov ah, 2               ; read
        mov al, 3               ; n o sectors
        mov ch, 0               ; cylinder
        mov cl, 2
        mov dh, 0
        mov bx, 0x7e00
        int 0x13

        mov ah, 0
        mov al, 0x12
        int 0x10

        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        lidt [idt]
        lgdt [gdt]

        ;; Protected mode
        mov eax, cr0
        or eax, 1
        mov cr0, eax

        jmp 0x08:protected      ; selector 8 (first after 0) in gdt

protected:
        use32

        mov eax, 0x10
        mov ds, eax
        mov es, eax
        mov fs, eax
        mov gs, eax
        mov ss, eax

        mov eax, 0x7bff
        mov esp, eax

        sti
        jmp 0x7e00

int_handle:
        pop eax
        iret

int_handle_kbd:
        jmp $
        pop eax
        iret

;;; GDT - Global Descriptor Table
;;; Access bits high to low:
;;;   present, privilege[2], 1,
;;;   execute, direction/conforming, read/write, accessed
gdt_start:
        dq 0
gdt_code:
        dw 0xffff               ; limit 0:15
        dw 0x0000               ; base 0:15
        db 0x00                 ; base 16:23
        db 0b10011010           ; access byte
        db 0x4f                 ; low = limit 16:19, high = flags
        db 0x00                 ; base 24:31
gdt_data:
        dw 0xffff               ; limit 0:15
        dw 0x0000               ; base 0:15
        db 0x00                 ; base 16:23
        db 0b10010010           ; access byte
        db 0x4f                 ; low = limit 16:19, high = flags
        db 0x00                 ; base 24:31
gdt:
        dw (gdt - gdt_start) - 1
        dd gdt_start

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

        times (0x15 * 8 - ($ - idt_start)) db 0x00
idt_keyboard:
        dw int_handle_kbd       ; offset 0:15
        dw 0x08                 ; code segment selector
        db 0x00                 ; unused
        db 0b1000_1110          ; type/attributes
        dw 0x0000               ; offset 16:31

idt:
        dw (idt - idt_start) - 1
        dd idt_start

mark_bootable:
        ;; Mark this device as bootable.
        times 510-($-$$) db 0   ; Go to byte 510
        db 0x55                 ; Byte 510 must be 0x55
        db 0xaa                 ; Byte 511 must be 0xaa
