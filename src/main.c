#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "winman.h"
#include "graphics.h"

#define halt() asm("hlt")

char buf[400*300*3];
char* winstr = "AAAAAAA 0123456789";

void kmain(void)
{
  set_key_event_handler(winman_key_event);
  asm("sti");
  winman_start();
  int c = 0xffffff;
  int i;
  for (i = 0; winstr[i] != '\0'; i++) {
    draw_char(i*8, 0, winstr[i], 0xffffff, buf, 400);
  }
  new_window(100, 200, 400, 300, buf);
  new_window(500, 100, 500, 500, &c);
  while (1) {
    halt();
  }
}
