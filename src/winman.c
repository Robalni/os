#include "winman.h"
#include "graphics.h"
#include "keyboard.h"

#define MAX_N_WINDOWS 16
static Window window_list[MAX_N_WINDOWS];
static int n_windows;

static int bgcolor = 0xd0d8e8;

static void draw_window(Window* w);
static void draw_everything(void);

void winman_start(void)
{
  fill_screen(bgcolor);
}

void new_window(int x, int y, int w, int h, char* content)
{
  if (n_windows < MAX_N_WINDOWS) {
    Window* win = &window_list[n_windows];
    win->x = x;
    win->y = y;
    win->w = w;
    win->h = h;
    win->content = content;
    n_windows++;
    draw_window(win);
  }
}

void move_window(Window* win, int dx, int dy)
{
  win->x += dx;
  win->y += dy;
  draw_everything();
}

void winman_key_event(int key)
{
  switch (key) {
  case 0x22:
    move_window(&window_list[0], 10, 2);
    break;
  }
}

static void draw_everything(void)
{
  int i;
  fill_screen(bgcolor);
  for (i = 0; i < n_windows; i++) {
    draw_window(&window_list[i]);
  }
}

static void draw_window(Window* w)
{
  int title_height = 24;
  int border_color = 0x666666;
  int padding = 2;
  draw_rect(w->x-padding, w->y-title_height, w->w+padding*2,
            w->h+title_height+padding, 0xcccccc);
  draw_border(w->x-padding, w->y-title_height, w->w+padding*2,
              w->h+title_height+padding, border_color);
  draw_rect(w->x, w->y, w->w, w->h, 0xffffff);
  //draw_border(w->x, w->y, w->w, w->h, border_color);
  if (w->content) {
    draw_content(w->x, w->y, w->w, w->h, w->content);
  }
}
