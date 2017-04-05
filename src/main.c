#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "winman.h"

#define halt() asm("hlt")
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) < 0 ? (-(x)) : (x))

static char * const vidmem2 = (char*)0xa0000;

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
