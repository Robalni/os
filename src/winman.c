#include "winman.h"
#include "graphics.h"
#include "keyboard.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? (-a) : (a))

#define MAX_N_WINDOWS 16
static Window window_list[MAX_N_WINDOWS];
static int n_windows;
static int focused;

static int super_down;

static int bgcolor = 0xdddddd;

static void draw_window(Window* win);
static void draw_window_r(Window* win, int x, int y, int w, int h);
static void draw_everything(int x, int y, int w, int h);

static int title_height = 24;
static int padding = 2;

void winman_start(void)
{
  init_graphics();
  fill_screen(bgcolor);
}

Window* new_window(int x, int y, int w, int h, int bgcolor,
                void (*key_event_handler)(int))
{
  if (n_windows < MAX_N_WINDOWS) {
    Window* win = &window_list[n_windows];
    win->x = x;
    win->y = y;
    win->w = w;
    win->h = h;
    win->content = (uint8_t*)(0x00ff0000 + n_windows*1024*768*3);
    int i;
    for (i = 0; i < w*h*3; i += 3) {
      win->content[i] = bgcolor;
      win->content[i+1] = bgcolor >> 8;
      win->content[i+2] = bgcolor >> 16;
    }
    win->key_event_handler = key_event_handler;
    n_windows++;
    draw_window(win);
    return win;
  }
  return 0;
}

void move_window(Window* win, int dx, int dy)
{
  int wx = win->x - padding - 1;
  int wy = win->y - title_height - 1;
  int ww = win->w + padding*2 + 2;
  int wh = win->h + padding + title_height + 2;
  win->x += dx;
  win->y += dy;
  draw_everything(MIN(wx + dx, wx), MIN(wy + dy, wy),
                  ww + ABS(dx), wh + ABS(dy));
}

void winman_key_event(int key)
{
  switch (key) {
  case 0x48:
    move_window(&window_list[focused], 0, -10);
    break;
  case 0x4b:
    move_window(&window_list[focused], -10, 0);
    break;
  case 0x4d:
    move_window(&window_list[focused], 10, 0);
    break;
  case 0x50:
    move_window(&window_list[focused], 0, 10);
    break;
  case 0x5b:
  case 0x5c:
    super_down = 1;
    break;
  case 0xdb:
  case 0xdc:
    super_down = 0;
    break;
  case 0x0f:
    if (super_down || 1) {
      focused = (focused + 1) % n_windows;
      draw_everything(0, 0, 1024, 768);
    }
    break;
  }
  Window* win = &window_list[focused];
  if (win->key_event_handler) {
    win->key_event_handler(key);
    draw_everything(win->x, win->y, win->w, win->h);
  }
}

Window* get_current_window(void)
{
  return &window_list[focused];
}

static void draw_everything(int x, int y, int w, int h)
{
  int i;
  draw_rect(x, y, w, h, bgcolor);
  for (i = 0; i < n_windows; i++) {
    draw_window_r(&window_list[i], x, y, w, h);
  }
}

static void draw_window(Window* win)
{
  draw_window_r(win, win->x - padding - 1, win->y - title_height - 1,
                win->w + padding*2 + 2, win->h + title_height + padding + 2);
}

static void draw_window_r(Window* win, int x, int y, int w, int h)
{
  int border_color = 0x999999;
  int window_color = 0xeeeeee;
  if (window_list + focused == win) {
    window_color = 0xcccccc;
  }
  draw_rect_r(win->x-padding, win->y-title_height, win->w+padding*2,
              title_height, x, y, w, h, window_color);
  draw_rect_r(win->x-padding, win->y, padding, win->h,
              x, y, w, h, window_color);
  draw_rect_r(win->x+win->w, win->y, padding, win->h,
              x, y, w, h, window_color);
  draw_rect_r(win->x-padding, win->y+win->h, win->w+padding*2, padding,
              x, y, w, h, window_color);
  draw_border(win->x-padding, win->y-title_height, win->w+padding*2,
              win->h+title_height+padding, border_color);
  if (win->content) {
    draw_content(win->x, win->y, win->w, win->h, win->content);
  }
}
