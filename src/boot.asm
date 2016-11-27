        use16

        org 0x7c00
        jmp bootloader

bootloader:
        ;; Stack
        mov ax, 0x7bff
        mov sp, ax

        mov ah, 2               ; read
        mov al, 7               ; n o sectors
        mov ch, 0               ; cylinder
        mov cl, 2
        mov dh, 0
        mov bx, 0x7e00
        int 0x13

        mov ah, 0
        mov al, 0x12
        mov al, 0x03
        int 0x10

        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
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

        jmp 0x7e00

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

mark_bootable:
        ;; Mark this device as bootable.
        times 510-($-$$) db 0   ; Go to byte 510
        db 0x55                 ; Byte 510 must be 0x55
        db 0xaa                 ; Byte 511 must be 0xaa
