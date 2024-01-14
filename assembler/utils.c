#include "utils.h"
#include <stdio.h>

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
