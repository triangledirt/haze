unsigned char sy_bit_from_char(unsigned char character, unsigned int index)
{
}

unsigned char sy_bit_from_int(unsigned int integer, unsigned int index)
{
}

#define ih_bit_get(value, bit_index) ((value >> (bit_index)) & (uint64_t) 1)

#define ih_bit_set(value, bit_index, bit_value)              \
  if (bit_value) { *value |= ((uint64_t) 1 << (bit_index)); } \
  else { *value &= ~((uint64_t) 1 << (bit_index)); }
