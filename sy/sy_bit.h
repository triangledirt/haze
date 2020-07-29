#ifndef sy_bit_h
#define sy_bit_h

unsigned char sy_bit_from_char(unsigned char character, unsigned int index);
unsigned char sy_bit_from_int(unsigned int integer, unsigned int index);
void sy_bit_to_char(unsigned char *character, unsigned int index,
  unsigned char value);
void sy_bit_to_int(unsigned int *integer, unsigned int index,
  unsigned char value);

#endif
