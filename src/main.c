#include "shell.h"
#include "keyboard.h"
#include "console.h"

#define halt() asm("hlt")
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) < 0 ? (-(x)) : (x))

static char * const vidmem2 = (char*)0xa0000;

void kmain(void)
{
  set_key_event_handler(shell_key_event);
  asm("sti");
  shell_start();
  while (1) {
    halt();
  }
}
