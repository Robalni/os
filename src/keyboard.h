#ifndef KEYBOARD_H
#define KEYBOARD_H

void set_key_event_handler(void (*handler)(int));

char kbd_to_char(int key, int shift);

#endif /* KEYBOARD_H */
