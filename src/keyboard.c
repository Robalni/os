#include "keyboard.h"

static const char * const chars_qwerty =
  "\x00 1234567890    "
  "qwertyiop;[]  "
  "asdfghjkl;'\\  "
  "zxcvbnm,./    ";
static const char * const chars_colemak =
  "\x00 1234567890-=  "
  "qwfpgjluy;[]  "
  "arstdhneio'` \\"
  "zxcvbkm,./    ";
static const char * const chars_colemak_shift =
  "\x00 !@#$%^&*()_+  "
  "QWFPGJLUY:{}  "
  "ARSTDHNEIO\"~ |"
  "ZXCVBKM<>?    ";
static void (*key_event_handler)(int) = 0;

void set_key_event_handler(void (*handler)(int))
{
  key_event_handler = handler;
}

void key_pressed(int key)
{
  if (key_event_handler) {
    key_event_handler(key);
  }
}

char kbd_to_char(int key, int shift)
{
  if (shift) {
    return chars_colemak_shift[key];
  } else {
    return chars_colemak[key];
  }
}
