#include "keyboard.h"

static void (*key_event_handler)(int) = 0;

void set_key_event_handler(void (*handler)(int))
{
  key_event_handler = handler;
}

void key_pressed(int key)
{
  if (key_event_handler) {
    key_event_handler(key);
  }
}
