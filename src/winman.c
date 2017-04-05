#include "winman.h"
#include "graphics.h"

void winman_start(void)
{
  fill_screen(0xd0d8e8);
}

void draw_window(int x, int y, int w, int h)
{
  int title_height = 24;
  int border_color = 0x666666;
  int padding = 2;
  draw_rect(x-padding, y-title_height, w+padding*2,
            h+title_height+padding, 0xcccccc);
  draw_border(x-padding, y-title_height, w+padding*2,
              h+title_height+padding, border_color);
  draw_rect(x, y, w, h, 0xffffff);
  //draw_border(x, y, w, h, border_color);
}
