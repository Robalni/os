        use32

section .text
        global start
        extern kmain

start:
        call kmain
        jmp $
