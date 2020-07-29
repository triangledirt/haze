#include <stdlib.h>

static unsigned char random_chars[256];
static unsigned int random_ints[1024];

unsigned char sy_random_char()
{
  static unsigned int i = 0;

  if (i != 256) {
    i++;
  } else {
    i = 0;
  }

  return random_chars[i];
}

unsigned int sy_random_int()
{
  static unsigned int i = 0;

  if (i != 1024) {
    i++;
  } else {
    i = 0;
  }

  return random_ints[i];
}

void sy_random_start()
{
  unsigned int i;

  for (i = 0; i < 256; i++) {
    random_chars[i] = (unsigned char) random() % 256;
  }

  for (i = 0; i < 1024; i++) {
    random_ints[i] = (unsigned int) random();
  }
}
