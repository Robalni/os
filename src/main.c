#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "winman.h"

#define halt() asm("hlt")

void kmain(void)
{
  //set_key_event_handler(shell_key_event);
  //asm("sti");
  //shell_start();
  winman_start();
  draw_window(100, 200, 400, 300);
  while (1) {
    halt();
  }
}
