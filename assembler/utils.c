#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// from emulator/instructions.c
uint16_t from_2_uint8_t_to_uint16_t(uint8_t u1, uint8_t u2){
    return ((uint16_t)u2 << 8) | u1;
}
uint8_t uint16_t_low(uint16_t u){
    return u & 0xFF;
}

uint8_t uint16_t_high(uint16_t u){
    return (u >> 8) & 0xFF;
}

void debug_print_uint8_buf(uint8_t* buf, size_t size){
    printf("buf : ");
    for (int i = 0; i < size; i++){
        printf("%#x ", buf[i]);
    }
    printf("\n");
}

void write_single_instruction_to_file(struct assembler_context* context, uint8_t instruction){
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-1);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);
}

void write_instruction_to_file(struct assembler_context* context, uint8_t instruction, uint8_t reg, uint8_t data1, uint8_t data2){
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction;
    buf[1] = reg;
    buf[2] = data1;
    buf[3] = data2;
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);
}
