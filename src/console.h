#ifndef CONSOLE_H
#define CONSOLE_H

enum color {
  BLACK, BLUE, GREEN, CYAN,
  RED, MAGENTA, BROWN, LIGHTGREY,
  DARKGREY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
  LIGHTRED, LIGHTMAGENTA, LIGHTBROWN, WHITE
};

void putchar_at(int x, int y, enum color color, char ch);

void putchar_here(enum color color, char ch);

void set_cursor(int cur);

void move_cursor(int x, int y);

void setmove_cursor(int x, int y);

void putchar(char ch);

int print(char *msg);

int printat(int x, int y, enum color color, char *msg);

void clear_screen(void);

#endif /* CONSOLE_H */
