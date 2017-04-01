#ifndef CONSOLE_H
#define CONSOLE_H

enum color {
  BLACK, BLUE, GREEN, CYAN,
  RED, MAGENTA, BROWN, LIGHTGREY,
  DARKGREY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
  LIGHTRED, LIGHTMAGENTA, LIGHTBROWN, WHITE
};

void putcharat(int x, int y, enum color color, char ch);

void set_cursor(int cur);

void putchar(char ch);

int print(char *msg);

int printat(int x, int y, enum color color, char *msg);

void clear_screen(void);

void console_key_event(int key);

#endif /* CONSOLE_H */
