#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "winman.h"
#include "graphics.h"

#define halt() asm("hlt")

unsigned char buf[400*300*3];
char* winstr = "AAAAAAA 0123456789";

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

void errmsg(int info)
{
  extern unsigned char** const vesamem;
  int i;
  char* e = "Error! General protection fault.";
  for (i = 0; e[i] != '\0'; i++) {
    draw_char(i*8, 0, e[i], 0xffffff, *vesamem, 1024, 0x990000);
  }
  draw_char(24, 16, n2ch(info&0xf), 0xffffff, *vesamem, 1024, 0x990000);
  info >>= 4;
  draw_char(16, 16, n2ch(info&0xf), 0xffffff, *vesamem, 1024, 0x990000);
  info >>= 4;
  draw_char(8, 16, n2ch(info&0xf), 0xffffff, *vesamem, 1024, 0x990000);
  info >>= 4;
  draw_char(0, 16, n2ch(info&0xf), 0xffffff, *vesamem, 1024, 0x990000);
  //draw_content(0, 0, 400, 300, buf);
}

void kmain(void)
{
  set_key_event_handler(winman_key_event);
  asm("sti");
  winman_start();
  new_window(100, 200, 400, 300, buf, shell_key_event);
  new_window(500, 100, 400, 500, (unsigned char*)3, 0);
  shell_start();
  while (1) {
    halt();
  }
}
