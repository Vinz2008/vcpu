#include <stdint.h>
#include <stddef.h>
#include "labels.h"

#define BIN_WRITE_BUF_SIZE 4

uint16_t from_2_uint8_t_to_uint16_t(uint8_t u1, uint8_t u2);
uint8_t uint16_t_low(uint16_t u);
uint8_t uint16_t_high(uint16_t u);
void debug_print_uint8_buf(uint8_t* buf, size_t size);

void write_instruction_to_file(struct assembler_context* context, uint8_t instruction, uint8_t reg, uint8_t data1, uint8_t data2);
void write_single_instruction_to_file(struct assembler_context* context, uint8_t instruction);