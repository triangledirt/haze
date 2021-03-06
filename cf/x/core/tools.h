#ifndef cf_x_core_tools_h
#define cf_x_core_tools_h

#include "cf/x/core/bit.h"
#include "cf/x/core/standard.h"

#define CF_X_CORE_BYTES_IN_A_KILOBYTE 1024
#define CF_X_CORE_BYTES_IN_A_MEGABYTE 1048576
#define CF_X_CORE_BYTES_IN_A_GIGABYTE 1073741824

#define CF_X_CORE_MAX_COLOR 2147483647

#define CF_X_CORE_SECONDS_PER_MINUTE 60
#define CF_X_CORE_SECONDS_PER_HOUR 3600
#define CF_X_CORE_SECONDS_PER_DAY 86400

#define CF_X_CORE_STANDARD_SLEEP_MICROSECONDS 1024

#define CF_X_CORE_WHITESPACE_DELIMITERS " \t\n\r"

#define cf_x_trace(message, ...) fprintf(stderr, message "() in %s:%d\n",  \
      ##__VA_ARGS__, __FILE__, __LINE__)

#define cf_x_disable_test() printf("  %s disabled\n", argv[0]); return 0

#define cf_x_core_get_bit(value, bit_index) ((value >> bit_index) & 1)

#define cf_x_core_hash(string) cf_x_core_hash_djb2_xor(string)

#define cf_x_core_implement() cf_x_trace("TODO: implement"); exit(19)

#define cf_x_core_max(a, b) ((a > b) ? a : b)

#define cf_x_core_min(a, b) ((a < b) ? a : b)

#define cf_x_core_trace(message, ...) fprintf(stderr, message "() in %s:%d\n", \
      ##__VA_ARGS__, __FILE__, __LINE__)

#define cf_x_core_trace_exit(message, ...) fprintf                         \
  (stderr, message"() in %s:%d\n", ##__VA_ARGS__, __FILE__, __LINE__);  \
  exit(22);

#define CF_X_CORE_TIME_STRING_LENGTH 15
typedef char cf_x_core_time_string_t[CF_X_CORE_TIME_STRING_LENGTH + 1];

typedef void *(*cf_x_core_thread_f)(void *thread_context);

cf_x_core_bool_t cf_x_core_stop_requested;

unsigned long cf_x_get_microseconds();

cf_x_core_bool_t cf_x_core_get_current_time_string(cf_x_core_time_string_t time_string);

void cf_x_core_do_nothing();

double cf_x_core_gray_coin_toss();

unsigned long cf_x_core_hash_djb2(char *string);

unsigned long cf_x_core_hash_djb2_xor(char *string);

unsigned long cf_x_core_hash_sdbm(char *string);

cf_x_core_bool_t cf_x_core_key_hit();

void cf_x_core_note_maximum_double(double *maximum, double candidate);

void cf_x_core_note_maximum_unsigned_long(unsigned long *maximum,
    unsigned long candidate);

double cf_x_core_percentage(double part, double whole);

void cf_x_core_request_stop();

void cf_x_core_seed_random(unsigned long seed);

void cf_x_core_seed_random_with_time();

void cf_x_core_set_bit_in_unsigned_char(unsigned char *c,
    unsigned short bit_index, cf_x_core_bit_t bit_value);

void cf_x_core_show_memory(void *location, unsigned short length);

char *cf_x_core_string_append(char *original, const char *addition);

char *cf_x_core_string_append_char(char *original, char addition);

char *cf_x_core_string_append_multiple(char *original, ...);

char *cf_x_core_string_append_n(char *original, char *addition,
    unsigned long addition_size);

char *cf_x_core_substring(char *string, unsigned short max_length);

void cf_x_core_terminal_block();

void cf_x_core_terminal_nonblock();

cf_x_core_bool_t cf_x_core_time_is_remaining_microseconds
(struct timeval *start_time, unsigned long max_wall_time_microseconds);

unsigned short cf_x_core_toss_coin();

void cf_x_core_truncate_string(char *string, unsigned short max_length);

unsigned long cf_x_core_wrap_index(long virtual_index, unsigned long range);

#endif
