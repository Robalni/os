#include "console.h"
#include "graphics.h"
#include "winman.h"
#include <stdint.h>

static int cursor = 80;
static unsigned short *base_video_port = (unsigned short*)0x0463;
static char * const vidmem = (char*)0xb8000;

#define DEFAULT_COLOR BLACK

static int colors[] = {
  0x000000, 0x0000cc, 0x00cc00, 0x00cccc,
  0xcc0000, 0xcc00cc, 0x884400, 0x888888,
  0x444444, 0x4444ff, 0x44ff44, 0x44ffff,
  0xcc4444, 0xcc44cc, 0xcccc00, 0xffffff
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
  Window* win = get_current_window();
  uint8_t* buf = win->content;
  draw_char(x%80*8, x/80*16 + y*16, ch, colors[color],
            win->content, win->w, 0xffffff);
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
  return;
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
  putchar_color(DEFAULT_COLOR, ch);
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
  return print_color(DEFAULT_COLOR, msg);
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
  for (i = 0; i < 50*18; i++) {
    putchar_at(i, 0, DEFAULT_COLOR, ' ');
  }
}

static void outb(int port, int val)
{
  asm("outb %%al, %%dx"
      :
      : "al"(val), "dx"(port));
}
