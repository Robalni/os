#include "shell.h"
#include "keyboard.h"
#include "console.h"

static int shift_down = 0;
static int ctrl_down = 0;
static int alt_down = 0;
static int super_down = 0;
#define MAX_LINE_LENGTH 50
static char line[MAX_LINE_LENGTH + 1];
static int line_at = 0;
static const char * const figures = "0123456789ABCDEF";

static int strcmp(char* s1, char* s2);

static int run_command(char *line);

static void show_prompt(void);

static void clear(void);

static void int2str(int number, char *str, int base);

static int pow(int base, int exp);

void shell_start(void)
{
  line_at = 0;
  clear();
  printat(0, 0, CYAN, "Last key pressed: (none)");
  print_color(GREEN, "\n  Welcome to this useless shell!\n\n");
  show_prompt();
}

void shell_key_event(int key)
{
  if (key == 0x2a || key == 0x36) {
    shift_down = 1;
  } else if (key == 0xaa || key == 0xb6) {
    shift_down = 0;
  } else if (key == 0x1d) {
    ctrl_down = 1;
  } else if (key == 0x9d) {
    ctrl_down = 0;
  } else if (key == 0x38) {
    alt_down = 1;
  } else if (key == 0xb8) {
    alt_down = 0;
  } else if (key == 0x5b || key == 0x5c) {
    super_down = 1;
  } else if (key == 0xdb || key == 0xdc) {
    super_down = 0;
  } else if (key == 0x1c) {
    line[line_at] = '\0';
    setmove_cursor(0, 1);
    int status = run_command(line);
    if (status == -1) {
      print_color(RED, "Unknown command: ");
      print(line);
      setmove_cursor(0, 1);
    }
    line_at = 0;
    show_prompt();
  } else if (key == 0x16 && ctrl_down) {
    clear();
    show_prompt();
  } else if (key == 0x2e && ctrl_down) {
    print("^C\n");
    line_at = 0;
    show_prompt();
  } else if (key == 0x22 && ctrl_down && line_at == 0) {
    shell_start();
  } else if (key == 0x0e) {
    if (line_at > 0) {
      line_at--;
      move_cursor(-1, 0);
      update_cursor();
      putchar_here(LIGHTGREY, ' ');
    }
  } else if (key == 0x48) {
    move_cursor(0, -1);
  } else if (key == 0x4b) {
    move_cursor(-1, 0);
  } else if (key == 0x4d) {
    move_cursor(1, 0);
  } else if (key == 0x50) {
    move_cursor(0, 1);
  } else if (key < 0x80) {
    if (line_at < MAX_LINE_LENGTH) {
      char ch = kbd_to_char(key, shift_down);
      line[line_at++] = ch;
      putchar(ch);
      update_cursor();
    }
  }
  printat(0, 0, CYAN, "Last key pressed: 0x");
  char key_str[10];
  int2str(key, key_str, 16);
  printat(20, 0, CYAN, key_str);
}

static int strcmp(char* s1, char* s2)
{
  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  return (*s1 > *s2) - (*s1 < *s2);
}

static int run_command(char *line)
{
  int i = 0;
  while (line[i] == ' ') {
    i++;
  }
  if (strcmp(line+i, "help") == 0) {
    print("Commands:\n");
    print("  help - Displays this help\n");
  } else if (line[i] != '\0') {
    return -1;
  }
  return 0;
}

static void show_prompt(void)
{
  line[line_at] = '\0';
  print_color(BROWN, "> ");
  print(line);
  update_cursor();
}

static void clear(void)
{
  clear_screen();
  set_cursor(80);
}

static void int2str(int number, char *str, int base)
{
  int pos = 0;
  int posvalue = pow(base, 3);
  while (pos < 4) {
    str[pos] = *(figures + number / posvalue % base);
    pos++;
    posvalue /= base;
  }
  str[pos] = '\0';
}

static int pow(int base, int exp)
{
  int value = 1;
  int i;
  for (i = 0; i < exp; i++) {
    value *= base;
  }
  return value;
}
