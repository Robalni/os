#include "shell.h"
#include "console.h"

static int shift_down = 0;
static int ctrl_down = 0;
#define MAX_LINE_LENGTH 50
static char line[MAX_LINE_LENGTH + 1];
static int line_at = 0;

static int run_command(char *line);

static void show_prompt(void);

static void clear(void);

void shell_start(void)
{
  line_at = 0;
  clear();
  printat(0, 0, CYAN, "Last key pressed: (none)");
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
  } else if (key == 0x1c) {
    line[line_at] = '\0';
    setmove_cursor(0, 1);
    int status = run_command(line);
    if (status == -1) {
      print("Unknown command: ");
      print(line);
      setmove_cursor(0, 1);
    }
    line_at = 0;
    show_prompt();
  } else if (key == 0x16 && ctrl_down) {
    clear();
  } else if (key == 0x0e) {
    if (line_at > 0) {
      line_at--;
      move_cursor(-1, 0);
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
    }
  }
  printat(0, 0, CYAN, "Last key pressed: 0x");
  char key_str[10];
  int2str(key, key_str, 16);
  printat(20, 0, CYAN, key_str);
}

static int run_command(char *line)
{
  int i = 0;
  while (line[i] == ' ') {
    i++;
  }
  if (line[i] != '\0') {
    return -1;
  }
  return 0;
}

static void show_prompt(void)
{
  print("$ ");
  update_cursor();
}

static void clear(void)
{
  line[line_at] = '\0';
  clear_screen();
  set_cursor(80);
  show_prompt();
  print(line);
  update_cursor();
}
