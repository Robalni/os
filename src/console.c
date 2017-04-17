#include "console.h"
#include "graphics.h"

static int cursor = 80;
static unsigned short *base_video_port = (unsigned short*)0x0463;
static char * const vidmem = (char*)0xb8000;

static int colors[] = {
  0x000000, 0x0000ff, 0x00ff00, 0x00ffff,
  0xff0000, 0xff00ff, 0xcc6600, 0xcccccc,
  0x666666, 0x6666ff, 0x66ff66, 0x66ffff,
  0xff6666, 0xff66ff, 0xffff00, 0xffffff
};

static void outb(int port, int val);

void putchar_at_(int x, int y, enum color color, char ch)
{
  char *vidmem = (char*)0xb8000;
  int i = (x + 80*y) * 2;
  vidmem[i] = ch;
  vidmem[i + 1] = color;
}

void putchar_at(int x, int y, enum color color, char ch)
{
  extern char buf[400*300*3];
  draw_char(x%80*8, x/80*16 + y*16, ch, colors[color], buf, 400);
}

void putchar_here(enum color color, char ch)
{
  putchar_at(cursor, 0, color, ch);
}

void set_cursor(int cur)
{
  cursor = cur;
}

void move_cursor(int x, int y)
{
  set_cursor(cursor + x + y*80);
}

void update_cursor(void)
{
  outb(*base_video_port, 0x0f);
  outb(*base_video_port + 1, cursor & 0xff);
  outb(*base_video_port, 0x0e);
  outb(*base_video_port + 1, (cursor>>8) & 0xff);
}

void setmove_cursor(int x, int y)
{
  set_cursor((cursor / 80 + y) * 80 + x);
}

void putchar(char ch)
{
  putchar_color(LIGHTGREY, ch);
}

void putchar_color(enum color color, char ch)
{
  if (ch == '\n') {
    setmove_cursor(0, 1);
  } else {
    putchar_at(cursor, 0, color, ch);
    cursor++;
  }
}

int print(char *msg)
{
  return print_color(LIGHTGREY, msg);
}

int print_color(enum color color, char *msg)
{
  int i = 0;
  while (msg[i] != '\0') {
    putchar_color(color, msg[i]);
    i++;
  }
  return i;
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
    putchar_at(i, 0, LIGHTGREY, ' ');
  }
}

static void outb(int port, int val)
{
  asm("outb %%al, %%dx"
      :
      : "al"(val), "dx"(port));
}
