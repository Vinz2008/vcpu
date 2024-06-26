#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
        case 0x05:
            return &context->r5;
        case 0x06:
            return &context->r6;
        case 0x07:
            return &context->r7;
        case 0x08:
            return &context->r8;
        case 0x09:
            return &context->r9;
        case 0x0A:
            return &context->r10;
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
    // number into reg
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    printf("instruction : load from number %d (%x) into reg %x\n", value, value, reg);
    *get_reg_address(context, reg) = value;
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

void instruction_cmp_reg_with_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    context->cmp_flag = (*get_reg_address(context, reg) == *get_reg_address(context, data2));
    context->is_greater_flag = (*get_reg_address(context, reg) > *get_reg_address(context, data2));
    context->is_lower_flag = (*get_reg_address(context, reg) < *get_reg_address(context, data2));
}

void instruction_cmp_reg_with_num(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    context->cmp_flag = (*get_reg_address(context, reg) == value);
    context->is_greater_flag = (*get_reg_address(context, reg) > value);
    context->is_lower_flag = (*get_reg_address(context, reg) < value);
}

void instruction_add_val_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) + value;
}

void instruction_add_reg_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = *get_reg_address(context, reg) + *get_reg_address(context, data2);
}

void instruction_sub_val_from_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) - value;
}

void instruction_sub_reg_from_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = *get_reg_address(context, reg) - *get_reg_address(context, data2);
}

void instruction_mul_val_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) * value;
}

void instruction_div_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) / value;
}

void instruction_mul_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = *get_reg_address(context, reg) * *get_reg_address(context, data2);
}

void instruction_div_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = *get_reg_address(context, reg) / *get_reg_address(context, data2);
}

void instruction_jump_always(struct emulator_context* context, uint16_t address){
    context->pc = address;
}

void instruction_jump_if_equ(struct emulator_context* context, uint16_t address){
    if (context->cmp_flag){
        context->pc = address;
    }
}

void instruction_jump_if_greater(struct emulator_context* context, uint16_t address){
    if (context->is_greater_flag){
        context->pc = address;
    }
}

void instruction_jump_if_lower(struct emulator_context* context, uint16_t address){
    if (context->is_lower_flag){
        context->pc = (int)address;
    }
}

void instruction_jump(struct emulator_context* context, uint8_t instruction, uint16_t address){
    /*printf("jump to %d\n", (int)address);
    printf("instruction in jump address : %x\n", context->mem[address]);*/
    switch (instruction){
    case 0x30:
        instruction_jump_if_equ(context, address);
        break;
    case 0x31:
        instruction_jump_if_greater(context, address);
        break;
    case 0x32:
        instruction_jump_if_lower(context, address);
        break;
    case 0x33:
        instruction_jump_always(context, address);
        break;
    default:
        printf("ERROR : Unknown jump instruction\n"); // should never happen
        exit(1);
    }   
}

void instruction_and_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) & value;
}

void instruction_and_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = *get_reg_address(context, reg) & *get_reg_address(context, data2);
}

void instruction_or_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) | value;
}

void instruction_or_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = *get_reg_address(context, reg) | *get_reg_address(context, data2);
}

void instruction_not_of_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = ~value;
}

void instruction_not_of_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = ~(*get_reg_address(context, data2));
}

void instruction_xor_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    *get_reg_address(context, reg) = *get_reg_address(context, reg) ^ value;
}

void instruction_xor_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2){
    *get_reg_address(context, reg) = *get_reg_address(context, reg) ^ *get_reg_address(context, data2);
}

void instruction_syscall(struct emulator_context* context){
    switch (context->r1){ // syscall number
        default:
            fprintf(stderr, "WARNING : Unknown syscall\n");
    }
}

void instruction_push_val(struct emulator_context* context, uint8_t data1, uint8_t data2){
    uint16_t value = from_2_uint8_t_to_uint16_t(data1, data2);
    context->mem[context->r10-1] = value;
    context->r10--;
}

void instruction_push_val_from_reg(struct emulator_context* context, uint8_t reg){
    context->mem[context->r10-1] = *get_reg_address(context, reg);
    context->r10--;
}

void instruction_pop_val(struct emulator_context* context, uint8_t reg){
    *get_reg_address(context, reg) = context->mem[context->r10];
    context->r10++;
}