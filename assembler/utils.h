#include <stdint.h>
#include <stddef.h>

#define BIN_WRITE_BUF_SIZE 4

uint16_t from_2_uint8_t_to_uint16_t(uint8_t u1, uint8_t u2);
uint8_t uint16_t_low(uint16_t u);
uint8_t uint16_t_high(uint16_t u);
void debug_print_uint8_buf(uint8_t* buf, size_t size);