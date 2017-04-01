#include "console.h"

static int cursor = 80;
static unsigned short *base_video_port = (unsigned short*)0x0463;
static char * const vidmem = (char*)0xb8000;

void putchar_at(int x, int y, enum color color, char ch)
{
  char *vidmem = (char*)0xb8000;
  int i = (x + 80*y) * 2;
  vidmem[i] = ch;
  vidmem[i + 1] = color;
}

void putchar_here(enum color color, char ch)
{
  putchar_at(cursor, 0, color, ch);
}

void set_cursor(int cur)
{
  cursor = cur;
  outb(*base_video_port, 0x0f);
  outb(*base_video_port + 1, cursor & 0xff);
  outb(*base_video_port, 0x0e);
  outb(*base_video_port + 1, (cursor>>8) & 0xff);
}

void move_cursor(int x, int y)
{
  set_cursor(cursor + x + y*80);
}

void setmove_cursor(int x, int y)
{
  set_cursor((cursor / 80 + y) * 80 + x);
}

void putchar(char ch)
{
  putchar_at(cursor, 0, LIGHTGREY, ch);
  set_cursor(cursor+1);
}

int print(char *msg)
{
  cursor += printat(cursor, 0, LIGHTGREY, msg);
}

int printat(int x, int y, enum color color, char *msg)
{
  int i = y * 80 + x;
  int msg_i = 0;
  while (msg[msg_i] != '\0') {
    putchar_at(i, 0, color, msg[msg_i]);
    i++;
    msg_i++;
  }
  return msg_i;
}

void clear_screen(void)
{
  int i;
  for (i = 0; i < 80*25; i++) {
    putchar_at(i, 0, LIGHTGREY, 0);
  }
}
