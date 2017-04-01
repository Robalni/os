#include "shell.h"
#include "keyboard.h"
#include "console.h"

#define halt() asm("hlt")
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) < 0 ? (-(x)) : (x))

static char * const vidmem2 = (char*)0xa0000;
static const char * const figures = "0123456789ABCDEF";

void outb(int port, int val);

void int2str(int number, char *str, int base);

int pow(int base, int exp);

void kmain(void)
{
  set_key_event_handler(shell_key_event);
  shell_start();
  while (1) {
    halt();
  }
}

void outb(int port, int val)
{
  asm("outb %%al, %%dx"
      :
      : "al"(val), "dx"(port));
}

void int2str(int number, char *str, int base)
{
  int pos = 0;
  int posvalue = pow(base, 3);
  while (pos < 4) {
    str[pos] = *(figures + number / posvalue % base);
    pos++;
    posvalue /= base;
  }
  str[pos] = '\0';
}

int pow(int base, int exp)
{
  int value = 1;
  int i;
  for (i = 0; i < exp; i++) {
    value *= base;
  }
  return value;
}
