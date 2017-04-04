#include "graphics.h"

static unsigned char** const vesamem = (unsigned char**)0x10;
static int scr_w = 1024;
static int scr_h = 768;

void fill_screen(int color)
{
  unsigned char* pos = vesamem[0];
  unsigned char* stop_at = pos + 1024*768*3;
  for (; pos < stop_at; pos += 3) {
    pos[0] = color;
    pos[0+1] = color >> 8;
    pos[0+2] = color >> 16;
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
      pos[ix] = color;
      pos[ix+1] = color >> 8;
      pos[ix+2] = color >> 16;
    }
    pos += scr_w3;
  }
}

void draw_pixel(int x, int y, int color)
{
  int pos = (y*scr_w + x) * 3;
  vesamem[0][pos] = color;
  vesamem[0][pos+1] = color >> 8;
  vesamem[0][pos+2] = color >> 16;
}
