#ifndef GRAPHICS_H
#define GRAPHICS_H

void fill_screen(int color);

void draw_pixel(int x, int y, int color);

void draw_rect(int x, int y, int w, int h, int color);

void draw_rect_r(int x, int y, int w, int h,
                 int x2, int y2, int w2, int h2, int color);

void draw_border(int x, int y, int w, int h, int color);

void draw_content(int x, int y, int w, int h, unsigned char* content);

void draw_char(int x, int y, char ch, int color, unsigned char* buf, int buf_w,
               int fill);

#endif /* GRAPHICS_H */
