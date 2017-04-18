#include "graphics.h"
#include "font.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

void draw_rect_r(int x, int y, int w, int h,
                 int x2, int y2, int w2, int h2, int color)
{
  int newx = MAX(x, x2);
  int newy = MAX(y, y2);
  draw_rect(newx, newy, MIN(x+w, x2+w2)-newx, MIN(y+h, y2+h2)-newy, color);
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

void draw_content(int x, int y, int w, int h, unsigned char* content)
{
  w *= 3;
  x *= 3;
  int scr_w3 = scr_w * 3;
  unsigned char* buf = &vesamem[0][y*scr_w3 + x];
  int i, j;
  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i += 3) {
      buf[i] = content[i];
      buf[i+1] = content[i+1];
      buf[i+2] = content[i+2];
    }
    buf += scr_w3;
    content += w;
  }
}

void draw_char(int x, int y, char ch, int color, unsigned char* buf, int buf_w,
               int fill)
{
  x *= 3;
  buf_w *= 3;
  int i, j;
  buf += y*buf_w + x;
  for (j = 0; j < 16; j++) {
    for (i = 0; i < 8; i++) {
      int c = font[ch*16+j] & (128>>i);
      if (c) {
        set_color(&buf[i*3], color);
      } else if (fill >= 0) {
        set_color(&buf[i*3], fill);
      }
    }
    buf += buf_w;
  }
}

static void set_color(unsigned char* pixel, int color)
{
  pixel[0] = color;
  pixel[1] = color >> 8;
  pixel[2] = color >> 16;
}
