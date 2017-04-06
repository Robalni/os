#ifndef GRAPHICS_H
#define GRAPHICS_H

void fill_screen(int color);

void draw_pixel(int x, int y, int color);

void draw_rect(int x, int y, int w, int h, int color);

void draw_border(int x, int y, int w, int h, int color);

void draw_content(int x, int y, int w, int h, char* content);

#endif /* GRAPHICS_H */
