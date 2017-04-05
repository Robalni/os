#include "graphics.h"

static unsigned char** const vesamem = (unsigned char**)0x10;
static int scr_w = 1024;
static int scr_h = 768;

static void set_color(unsigned char* pixel, int color);

void fill_screen(int color)
{
  unsigned char* pos = vesamem[0];
  unsigned char* stop_at = pos + 1024*768*3;
  for (; pos < stop_at; pos += 3) {
    set_color(pos, color);
  }
}

void draw_rect(int x, int y, int w, int h, int color)
{
  int ix, iy;
  int scr_w3 = scr_w * 3;
  unsigned char* pos = *vesamem + (y*scr_w + x) * 3;
  w *= 3;
  for (iy = 0; iy < h; iy++) {
    for (ix = 0; ix < w; ix += 3) {
      set_color(&pos[ix], color);
    }
    pos += scr_w3;
  }
}

void draw_pixel(int x, int y, int color)
{
  int pos = (y*scr_w + x) * 3;
  set_color(&vesamem[0][pos], color);
}

void draw_border(int x, int y, int w, int h, int color)
{
  y--;
  x--;
  h += 1;
  w += 1;
  draw_rect(x, y, w, 1, color);
  draw_rect(x+1, y+h, w, 1, color);
  draw_rect(x, y+1, 1, h, color);
  draw_rect(x+w, y, 1, h, color);
}

static void set_color(unsigned char* pixel, int color)
{
  pixel[0] = color;
  pixel[1] = color >> 8;
  pixel[2] = color >> 16;
}
