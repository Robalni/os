#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "winman.h"
#include "graphics.h"

#define halt() asm("hlt")

unsigned char buf[400*300*3];
char* winstr = "AAAAAAA 0123456789";

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
