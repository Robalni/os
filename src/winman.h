#ifndef WINMAN_H
#define WINMAN_H

#include <stdint.h>

typedef struct {
  int border;
  int x;
  int y;
  int w;
  int h;
  uint8_t* content;
  void (*key_event_handler)(int);
} Window;

void winman_start(void);

Window* new_window(int x, int y, int w, int h, int bgcolor,
                   void (*key_event_handler)(int));

void move_window(Window* win, int dx, int dy);

void winman_key_event(int key);

Window* get_current_window(void);

#endif /* WINMAN_H */
