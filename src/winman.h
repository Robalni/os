#ifndef WINMAN_H
#define WINMAN_H

typedef struct {
  int border;
  int x;
  int y;
  int w;
  int h;
  unsigned char* content;
  void (*key_event_handler)(int);
} Window;

void winman_start(void);

void new_window(int x, int y, int w, int h, unsigned char* content,
                void (*key_event_handler)(int));

void move_window(Window* win, int dx, int dy);

void winman_key_event(int key);

#endif /* WINMAN_H */
