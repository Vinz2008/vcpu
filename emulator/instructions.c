#include <stdint.h>
#include <stdio.h>
#include "context.h"


uint16_t* get_reg_address(struct emulator_context* context, uint8_t reg){
    switch (reg){
        case 0x00:
            return &context->r0;
        case 0x01:
            return &context->r1;
        case 0x02:
            return &context->r2;
        case 0x03:
            return &context->r3;
        case 0x04:
            return &context->r4;
        default:
            return NULL;
    }
}

uint16_t from_2_uint8_t_to_uint16_t(uint8_t u1, uint8_t u2){
    return ((uint16_t)u2 << 8) | u1;
}

uint8_t uint16_t_low(uint16_t u){
    return u & 0xFF;
}

uint8_t uint16_t_high(uint16_t u){
    return (u >> 8) & 0xFF;
}


void instruction_load_from_mem_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t address = from_2_uint8_t_to_uint16_t(data1, data2);
    printf("instruction : load from mem %x into reg %x\n", address, reg);
    printf("load %d\n", context->mem[address]);
    *get_reg_address(context, reg) = context->mem[address];
}


void instruction_load_from_reg_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    // from reg to reg
    // second param is a register
    uint8_t reg_from = data2; 
    printf("instruction : load from reg %x into reg %x\n", reg_from, reg);
    printf("load %d\n", *get_reg_address(context, reg_from));
    *get_reg_address(context, reg) = *get_reg_address(context, reg_from);
}

void instruction_load_from_num_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    /*if (data1 == 0x00){
        // from reg to reg
        // second param is a register
        uint8_t reg_from = data2; 
        printf("instruction : load from reg %x into reg %x\n", reg_from, reg);
        printf("load %d\n", *get_reg_address(context, reg_from));
        *get_reg_address(context, reg) = *get_reg_address(context, reg_from);
    */
    //} else {
        // number into reg
        uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
        printf("instruction : load from number %d (%x) into reg %x\n", value, value, reg);
        *get_reg_address(context, reg) = value;


        /*uint16_t address = from_2_uint8_t_to_uint16_t(data1, data2);
        printf("instruction : load from mem %x into reg %x\n", address, reg);
        *get_reg_address(context, reg) = context->mem[address];*/

    //}
}


void instruction_store_from_reg_to_mem(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t address = from_2_uint8_t_to_uint16_t(data1, data2);
    context->mem[address] = *get_reg_address(context, reg);
}

// high 8 bits of reg
void instruction_store_from_reg_to_mem_high(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t address = from_2_uint8_t_to_uint16_t(data1, data2);
    context->mem[address] = uint16_t_high(*get_reg_address(context, reg));
}


// low 8 bits of reg
void instruction_store_from_reg_to_mem_low(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t address = from_2_uint8_t_to_uint16_t(data1, data2);
    context->mem[address] = uint16_t_low(*get_reg_address(context, reg));
}

void instruction_compare_reg_with_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    context->is_cmp_true = (*get_reg_address(context, reg) == *get_reg_address(context, data2));
}

void instruction_compare_reg_with_num(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    context->is_cmp_true = (*get_reg_address(context, reg) == value);
}

void instruction_add_val_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) + value;
}