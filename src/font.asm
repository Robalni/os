        global font
font:
        times ' '*0x10-($-$$) db 0b01010101

        times 16 db 0b00000000

        times '0'*0x10-($-$$) db 0b10101010

        db 0b00000000
        db 0b00011000
        db 0b00100100
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01011010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b00100100
        db 0b00011000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00010000
        db 0b00110000
        db 0b01010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b01111100
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00011000
        db 0b00100100
        db 0b01000010
        db 0b00000010
        db 0b00000010
        db 0b00000100
        db 0b00001000
        db 0b00010000
        db 0b00100000
        db 0b01000000
        db 0b01111110
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00111000
        db 0b01000100
        db 0b00000010
        db 0b00000010
        db 0b00000100
        db 0b00111000
        db 0b00000100
        db 0b00000010
        db 0b00000010
        db 0b01000100
        db 0b00111000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01111110
        db 0b00000010
        db 0b00000010
        db 0b00000010
        db 0b00000010
        db 0b00000010
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01111110
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01111000
        db 0b00000100
        db 0b00000010
        db 0b00000010
        db 0b01000010
        db 0b00100100
        db 0b00011000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00011000
        db 0b00100100
        db 0b01000010
        db 0b01000000
        db 0b01011000
        db 0b01100100
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b00100100
        db 0b00011000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01111110
        db 0b00000010
        db 0b00000010
        db 0b00000100
        db 0b00000100
        db 0b00001000
        db 0b00001000
        db 0b00010000
        db 0b00010000
        db 0b00100000
        db 0b00100000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00011000
        db 0b00100100
        db 0b01000010
        db 0b01000010
        db 0b00100100
        db 0b00011000
        db 0b00100100
        db 0b01000010
        db 0b01000010
        db 0b00100100
        db 0b00011000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00111000
        db 0b01000100
        db 0b10000010
        db 0b10000010
        db 0b10000010
        db 0b01000110
        db 0b00111010
        db 0b00000010
        db 0b00000010
        db 0b00000100
        db 0b00111000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        times 'A'*0x10-($-$$) db 0b10101010

        db 0b00000000
        db 0b00011000
        db 0b00100100
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01111110
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01111000
        db 0b01000100
        db 0b01000010
        db 0b01000010
        db 0b01000100
        db 0b01111000
        db 0b01000100
        db 0b01000010
        db 0b01000010
        db 0b01000100
        db 0b01111000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00011110
        db 0b00100000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b00100000
        db 0b00011110
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01111000
        db 0b01000100
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000100
        db 0b01111000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01111110
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01111110
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01111110
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01111110
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01111110
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        times 'a'*0x10-($-$$) db 0b10101010

        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00011110
        db 0b00100010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000110
        db 0b00111010
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b01011100
        db 0b01100010
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000100
        db 0b01111000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00011100
        db 0b00100010
        db 0b01000000
        db 0b01000000
        db 0b01000000
        db 0b00100010
        db 0b00011100
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00000010
        db 0b00000010
        db 0b00000010
        db 0b00000010
        db 0b00011010
        db 0b00100110
        db 0b01000010
        db 0b01000010
        db 0b01000010
        db 0b01000110
        db 0b00111010
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00011100
        db 0b00100010
        db 0b01000010
        db 0b01111100
        db 0b01000000
        db 0b01000010
        db 0b00111100
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000

        db 0b00000000
        db 0b00001100
        db 0b00010010
        db 0b00010000
        db 0b00010000
        db 0b01111110
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00010000
        db 0b00000000
        db 0b00000000
        db 0b00000000
        db 0b00000000
