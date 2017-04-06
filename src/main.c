#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "winman.h"

#define halt() asm("hlt")

void kmain(void)
{
  set_key_event_handler(winman_key_event);
  asm("sti");
  winman_start();
  int c = 0xffffff;
  new_window(100, 200, 400, 300, &c);
  new_window(500, 100, 500, 500, &c);
  while (1) {
    halt();
  }
}
