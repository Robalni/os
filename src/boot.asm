        use16

        org 0x7c00
        jmp bootloader

bootloader:
        ;; Stack
        mov ax, 0x7bff
        mov sp, ax

        mov ah, 2               ; read
        mov al, 16              ; n o sectors
        mov ch, 0               ; cylinder
        mov cl, 2
        mov dh, 0
        mov bx, 0x7e00
        int 0x13

        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        lgdt [gdt]

        call set_vesa_mode

        ;; Protected mode
        mov eax, cr0
        or eax, 1
        mov cr0, eax

        jmp 0x08:protected      ; selector 8 (first after 0) in gdt

set_vesa_mode:
        ;; Choose segment and offset.
        mov ax, 0x10
        mov es, ax
        mov di, 0x00

        ;; TODO: Put "VBE2" in [es:di]

        ;; Get vbe info.
        mov ax, 0x4f00
        int 0x10
        cmp ax, 0x004f
        jne vesa_error

        ;; Check the response.
        mov eax, [es:di]
        cmp eax, 'VESA'
        jne vesa_error

        ;; TODO: Select a good mode.

        ;; Get mode info.
        mov ax, 0x4f01
        mov cx, 0x0118
        int 0x10
        cmp ax, 0x004f
        jne vesa_error

        ;; Set vbe mode
        mov ax, 0x4f02
        mov bx, 0x4118
        int 0x10
        cmp ax, 0x004f
        jne vesa_error

        mov eax, [es:di+40]     ; +40 to find the framebuffer address
        mov [0x10], eax

        ret

vesa_error:
        mov si, .msg
        call println
        jmp halt
.msg:   db "VESA error!", 0

;;; Prints a message. You should put the address of the message in si.
;;; A message must be null terminated.
print:
        mov ah, 0x0e
.loop:
        lodsb
        cmp al, 0
        je .end
        int 0x10
        jmp .loop
.end:
        ret

;;; Prints a message + line break. You shold put the address of the
;;; message in si. A message must be null terminated.
println:
        call print
        mov al, 0x0d
        int 0x10
        mov al, 0x0a
        int 0x10
        ret

halt:
        mov si, .msg
        call println
        cli
        hlt
.msg:   db "System halted.", 0

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
