#include "graphics.h"
#include "font.h"
#include <stdint.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct vbe_mode_info {
  uint8_t unused1[16];
  uint16_t pitch;
  uint16_t width;
  uint16_t height;
  char unused2[3];
  uint8_t bpp;
  char unused3[14];
  uint32_t fb_addr;
} __attribute__((packed));

static uint16_t pitch;
uint8_t* vesamem;
static uint16_t scr_w;
static uint16_t scr_h;
static uint8_t bypp;

static void set_color(uint8_t* pixel, int color);

void init_graphics(void)
{
  static struct vbe_mode_info* v = (struct vbe_mode_info*)0x2000;
  pitch = v->pitch;
  scr_w = v->width;
  scr_h = v->height;
  bypp = v->bpp / 8;
  vesamem = (uint8_t*)v->fb_addr;
}

void fill_screen(int color)
{
  draw_rect(0, 0, scr_w, scr_h, color);
}

void draw_rect(int x, int y, int w, int h, int color)
{
  int ix, iy;
  uint8_t* pos = vesamem + y * pitch + x * bypp;
  w *= bypp;
  for (iy = 0; iy < h; iy++) {
    for (ix = 0; ix < w; ix += bypp) {
      set_color(&pos[ix], color);
    }
    pos += pitch;
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
  int pos = y * pitch + x * bypp;
  set_color(&vesamem[pos], color);
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

void draw_content(int x, int y, int w, int h, uint8_t* content)
{
  w *= bypp;
  x *= bypp;
  uint8_t* buf = &vesamem[y * pitch + x];
  int i, j;
  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i += bypp) {
      buf[i] = content[i];
      buf[i+1] = content[i+1];
      buf[i+2] = content[i+2];
    }
    buf += pitch;
    content += w;
  }
}

void draw_char(int x, int y, char ch, int color, uint8_t* buf, int buf_w,
               int fill)
{
  x *= bypp;
  buf_w *= bypp;
  int i, j;
  buf += y*buf_w + x;
  for (j = 0; j < 16; j++) {
    for (i = 0; i < 8; i++) {
      int c = font[ch*16+j] & (128>>i);
      if (c) {
        set_color(&buf[i*bypp], color);
      } else if (fill >= 0) {
        set_color(&buf[i*bypp], fill);
      }
    }
    buf += buf_w;
  }
}

static void set_color(uint8_t* pixel, int color)
{
  pixel[0] = color;
  pixel[1] = color >> 8;
  pixel[2] = color >> 16;
}
