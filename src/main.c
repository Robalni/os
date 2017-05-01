#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "winman.h"
#include "graphics.h"

#define halt() asm("hlt")

char n2ch(int n)
{
  if (n < 0) {
    return '?';
  } else if (n < 10) {
    return n + '0';
  } else if (n < 16) {
    return n - 10 + 'A';
  } else {
    return '?';
  }
}

void errmsg(char* message, int info)
{
  extern unsigned char* vesamem;
  int i;
  char* e = "Error: ";
  for (i = 0; e[i] != '\0'; i++) {
    draw_char(i*8, 0, e[i], 0xffffff, vesamem, 1024, 0x990000);
  }
  for (i = 0; message[i] != '\0'; i++) {
    draw_char((i+7)*8, 0, message[i], 0xffffff, vesamem, 1024, 0x990000);
  }
  draw_char(24, 16, n2ch(info&0xf), 0xffffff, vesamem, 1024, 0x990000);
  info >>= 4;
  draw_char(16, 16, n2ch(info&0xf), 0xffffff, vesamem, 1024, 0x990000);
  info >>= 4;
  draw_char(8, 16, n2ch(info&0xf), 0xffffff, vesamem, 1024, 0x990000);
  info >>= 4;
  draw_char(0, 16, n2ch(info&0xf), 0xffffff, vesamem, 1024, 0x990000);
}

void kmain(void)
{
  set_key_event_handler(winman_key_event);
  asm("sti");
  winman_start();
  Window* win1 = new_window(100, 200, 400, 300, 0xffffff, shell_key_event);
  Window* win2 = new_window(500, 100, 400, 500, 0xffffff, shell_key_event);
  shell_start();
  while (1) {
    halt();
  }
}
