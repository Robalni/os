#include "console.h"

static int shift_down = 0;
static int ctrl_down = 0;
static int cursor = 80;
static unsigned short *base_video_port = (unsigned short*)0x0463;
static char * const vidmem = (char*)0xb8000;
static const char * const kbd_chars_qwerty =
  "\x00 1234567890    "
  "qwertyiop;[]  "
  "asdfghjkl;'\\  "
  "zxcvbnm,./    ";
static const char * const kbd_chars_colemak =
  "\x00 1234567890-=  "
  "qwfpgjluy;[]  "
  "arstdhneio'` \\"
  "zxcvbkm,./    ";
static const char * const kbd_chars_colemak_shift =
  "\x00 !@#$%^&*()_+  "
  "QWFPGJLUY:{}  "
  "ARSTDHNEIO\"~ |"
  "ZXCVBKM<>?    ";

void putcharat(int x, int y, enum color color, char ch)
{
  char *vidmem = (char*)0xb8000;
  int i = (x + 80*y) * 2;
  vidmem[i] = ch;
  vidmem[i + 1] = color;
}

void set_cursor(int cur)
{
  cursor = cur;
  outb(*base_video_port, 0x0f);
  outb(*base_video_port + 1, cursor & 0xff);
  outb(*base_video_port, 0x0e);
  outb(*base_video_port + 1, (cursor>>8) & 0xff);
}

void putchar(char ch)
{
  putcharat(cursor, 0, LIGHTGREY, ch);
  set_cursor(cursor+1);
}

int print(char *msg)
{
  cursor += printat(cursor, 0, LIGHTGREY, msg);
}

int printat(int x, int y, enum color color, char *msg)
{
  int i = y * 80 + x;
  int msg_i = 0;
  while (msg[msg_i] != '\0') {
    putcharat(i, 0, color, msg[msg_i]);
    i++;
    msg_i++;
  }
  return msg_i;
}

void clear_screen(void)
{
  int i;
  for (i = 0; i < 80*25; i++) {
    putcharat(i, 0, LIGHTGREY, 0);
  }
}

void console_key_event(int key)
{
  if (key == 0x2a || key == 0x36) {
    shift_down = 1;
  } else if (key == 0xaa || key == 0xb6) {
    shift_down = 0;
  } else if (key == 0x1d) {
    ctrl_down = 1;
  } else if (key == 0x9d) {
    ctrl_down = 0;
  } else if (key == 0x1c) {
    set_cursor(cursor / 80 * 80 + 80);
  } else if (key == 0x16 && ctrl_down) {
    clear_screen();
    set_cursor(80);
  } else if (key == 0x0e) {
    set_cursor(cursor-1);
    putcharat(cursor, 0, LIGHTGREY, ' ');
  } else if (key == 0x48) {
    set_cursor(cursor-80);
  } else if (key == 0x4b) {
    set_cursor(cursor-1);
  } else if (key == 0x4d) {
    set_cursor(cursor+1);
  } else if (key == 0x50) {
    set_cursor(cursor+80);
  } else if (key < 0x80) {
    if (shift_down) {
      putchar(kbd_chars_colemak_shift[key]);
    } else {
      putchar(kbd_chars_colemak[key]);
    }
  }
  printat(0, 0, CYAN, "Last key pressed: 0x");
  char key_str[10];
  int2str(key, key_str, 16);
  printat(20, 0, CYAN, key_str);
}
