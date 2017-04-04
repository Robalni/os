#include "shell.h"
#include "keyboard.h"
#include "console.h"
#include "graphics.h"

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
  fill_screen(0xdddddd);
  draw_rect(411, 283, 202, 202, 0x77aa55);
  draw_rect(412, 284, 200, 200, 0xaacc99);
  while (1) {
    halt();
  }
}
