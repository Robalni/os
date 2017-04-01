#include "shell.h"
#include "console.h"

static int shift_down = 0;
static int ctrl_down = 0;

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
    setmove_cursor(0, 1);
  } else if (key == 0x16 && ctrl_down) {
    clear_screen();
    set_cursor(80);
  } else if (key == 0x0e) {
    move_cursor(-1, 0);
    putchar_here(LIGHTGREY, ' ');
  } else if (key == 0x48) {
    move_cursor(0, -1);
  } else if (key == 0x4b) {
    move_cursor(-1, 0);
  } else if (key == 0x4d) {
    move_cursor(1, 0);
  } else if (key == 0x50) {
    move_cursor(0, 1);
  } else if (key < 0x80) {
    putchar(kbd_to_char(key, shift_down));
  }
  printat(0, 0, CYAN, "Last key pressed: 0x");
  char key_str[10];
  int2str(key, key_str, 16);
  printat(20, 0, CYAN, key_str);
}
