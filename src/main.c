#define halt() asm("hlt")
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) < 0 ? (-(x)) : (x))

static char * const vidmem = (char*)0xb8000;
static char * const vidmem2 = (char*)0xa0000;
static const char * const figures = "0123456789ABCDEF";
int cursor = 80;
int shift_down = 0;
int ctrl_down = 0;
unsigned short *base_video_port = (unsigned short*)0x0463;
static const char * const kbd_chars_qwerty =
  "\x00 1234567890    "
  "qwertyiop;[]  "
  "asdfghjkl;'\\  "
  "zxcvbnm,./    ";
static const char * const kbd_chars_colemak =
  "\x00 1234567890-=  "
  "qwfpgjluy;[]  "
  "arstdhneio'` \\"
  "zxcvbkm,./    ";
static const char * const kbd_chars_colemak_shift =
  "\x00 !@#$%^&*()_+  "
  "QWFPGJLUY:{}  "
  "ARSTDHNEIO\"~ |"
  "ZXCVBKM<>?    ";

enum color {
  BLACK, BLUE, GREEN, CYAN,
  RED, MAGENTA, BROWN, LIGHTGREY,
  DARKGREY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
  LIGHTRED, LIGHTMAGENTA, LIGHTBROWN, WHITE
};

void putcharat(int x, int y, enum color color, char ch);

void outb(int port, int val);

void set_cursor(int cur);

void putchar(char ch);

int print(char *msg);

int printat(int x, int y, enum color color, char *msg);

void int2str(int number, char *str, int base);

int pow(int base, int exp);

void clear_screen(void);

void kmain(void)
{
  clear_screen();
  printat(0, 0, CYAN, "Last key pressed: (none)");
  set_cursor(80);
  while (1) {
    halt();
  }
}

void putcharat(int x, int y, enum color color, char ch)
{
  char *vidmem = (char*)0xb8000;
  int i = (x + 80*y) * 2;
  vidmem[i] = ch;
  vidmem[i + 1] = color;
}

void outb(int port, int val)
{
  asm("outb %%al, %%dx"
      :
      : "al"(val), "dx"(port));
}

void set_cursor(int cur)
{
  cursor = cur;
  outb(*base_video_port, 0x0f);
  outb(*base_video_port + 1, cursor & 0xff);
  outb(*base_video_port, 0x0e);
  outb(*base_video_port + 1, (cursor>>8) & 0xff);
}

void putchar(char ch)
{
  putcharat(cursor, 0, LIGHTGREY, ch);
  set_cursor(cursor+1);
}

int print(char *msg)
{
  cursor += printat(cursor, 0, LIGHTGREY, msg);
}

int printat(int x, int y, enum color color, char *msg)
{
  int i = y * 80 + x;
  int msg_i = 0;
  while (msg[msg_i] != '\0') {
    putcharat(i, 0, color, msg[msg_i]);
    i++;
    msg_i++;
  }
  return msg_i;
}

void int2str(int number, char *str, int base)
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

int pow(int base, int exp)
{
  int value = 1;
  int i;
  for (i = 0; i < exp; i++) {
    value *= base;
  }
  return value;
}

void key_pressed(int key)
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
    set_cursor(cursor / 80 * 80 + 80);
  } else if (key == 0x16 && ctrl_down) {
    clear_screen();
    set_cursor(80);
  } else if (key == 0x0e) {
    set_cursor(cursor-1);
    putcharat(cursor, 0, LIGHTGREY, ' ');
  } else if (key == 0x48) {
    set_cursor(cursor-80);
  } else if (key == 0x4b) {
    set_cursor(cursor-1);
  } else if (key == 0x4d) {
    set_cursor(cursor+1);
  } else if (key == 0x50) {
    set_cursor(cursor+80);
  } else if (key < 0x80) {
    if (shift_down) {
      putchar(kbd_chars_colemak_shift[key]);
    } else {
      putchar(kbd_chars_colemak[key]);
    }
  }
  printat(0, 0, CYAN, "Last key pressed: 0x");
  char key_str[10];
  int2str(key, key_str, 16);
  printat(20, 0, CYAN, key_str);
}

void clear_screen(void)
{
  int i;
  for (i = 0; i < 80*25; i++) {
    putcharat(i, 0, LIGHTGREY, 0);
  }
}
