#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "context.h"
#include "instructions.h"

//#define MEM_SIZE 4096

// max size of memory possible
#define MEM_SIZE 65536

int main(int argc, char** argv){
    if (argc < 2){
        printf("missing file for emulator\n");
        exit(1);
    }
    printf("argc : %d\n", argc);
    char* filename = argv[1];
    printf("filename : %s\n", filename);
    struct emulator_context* context = malloc(sizeof(struct emulator_context));
    //context->code = malloc(sizeof(uint8_t) * 1);
    context->mem = malloc(sizeof(uint8_t) * (MEM_SIZE+1));
    if (!context->mem){
        fprintf(stderr, "Error when allocating the memory of the virtual cpu\n");
        exit(1);
    }
    //context->mem[0xffff] = 3;
    context->r10 = 0xffff; // setting the stack pointer to the end of the memory
    context->cmp_flag = false;
    context->is_greater_flag = false;
    context->is_lower_flag = false;
    int i = 0;
    FILE* f = fopen(filename, "rb");
    //while (fread(&context->code[i],sizeof(uint8_t), 1, f) > 0){
    while (fread(&context->mem[i],sizeof(uint8_t), 1, f) > 0){
        //printf("%p\n", context->code[i]);
        //context->code = realloc(context->code, sizeof(uint8_t) * (i + 1));
        i++;
    }
    context->code_size = i;
    printf("code size : %d\n", context->code_size);
    /*for (int i = 0; i < context->code_size; i++){
        printf("instruction : %x\n", context->code[i]);
    }*/
    //for (int i = 0; i < context->code_size; i += 4){

    bool is_last_instruction_cmp = false;

    for (context->pc = 0; context->pc < context->code_size; context->pc += 4){
        uint8_t instruction =  context->mem[context->pc];
        uint8_t reg = context->mem[context->pc+1];
        uint8_t data1 = context->mem[context->pc+2];
        uint8_t data2 = context->mem[context->pc+3];
        
        if (!is_last_instruction_cmp){
            context->cmp_flag = false;
            context->is_greater_flag = false;
            context->is_lower_flag = false;
        }
        is_last_instruction_cmp = false;


        switch (instruction){
            case 0x00:
                printf("LOAD from num\n");
                //uint16_t address = ((uint16_t)data2 << 8) | data1;
                instruction_load_from_num_to_reg(context, reg, data1, data2);
                break;
            case 0x01:
                printf("LOAD from reg\n");
                instruction_load_from_reg_to_reg(context, reg, data1, data2);
                break;
            case 0x02:
                printf("LOAD from mem\n");
                instruction_load_from_mem_to_reg(context, reg, data1, data2);
                break;
            case 0x10:
                printf("STORE to reg\n");
                instruction_store_from_reg_to_mem(context, reg, data1, data2);
                break;
            case 0x11:
                printf("STORE to reg high 8 bits\n");
                instruction_store_from_reg_to_mem_high(context, reg, data1, data2);
                break;
            case 0x12:
                printf("STORE to reg low 8 bits\n");
                instruction_store_from_reg_to_mem_low(context, reg, data1, data2);
                break;
            case 0x20:
                printf("CMP with reg\n");
                instruction_cmp_reg_with_reg(context, reg, data1, data2);
                break;
            case 0x21:
                printf("CMP with num\n");
                instruction_cmp_reg_with_num(context, reg, data1, data2);
                break;
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
                int address = from_2_uint8_t_to_uint16_t(data1, data2);
                printf("JUMP to %d\n", (int)address);
                instruction_jump(context, instruction, address);
                break;
            case 0x40:
                printf("ADD val to reg\n");
                instruction_add_val_to_reg(context, reg, data1, data2);
                break;
            case 0x41:
                printf("SUB val from reg\n");
                instruction_sub_val_from_reg(context, reg, data1, data2);
                break;
            case 0x42:
                printf("ADD reg to reg\n");
                instruction_add_reg_to_reg(context, reg, data1, data2);
                break;
            case 0x43:
                printf("SUB reg from reg\n");
                instruction_sub_reg_from_reg(context, reg, data1, data2);
                break;
            case 0x44:
                printf("MUL val and reg\n");
                instruction_mul_val_and_reg(context, reg, data1, data2);
                break;
            case 0x45:
                printf("DIV reg and val\n");
                instruction_div_reg_and_val(context, reg, data1, data2);
                break;
            case 0x46:
                printf("MUL reg and reg\n");
                instruction_mul_reg_and_reg(context, reg, data1, data2);
                break;
            case 0x47:
                printf("DIV reg and reg\n");
                instruction_div_reg_and_reg(context, reg, data1, data2);
                break;
            case 0x50:
                printf("PUSH value\n");
                instruction_push_val(context, data1, data2);
                break;
            case 0x51:
                printf("PUSH value from reg\n");
                instruction_push_val_from_reg(context, reg);
                break;
            case 0x52:
                printf("POP value from the stack\n");
                instruction_pop_val(context, reg);
                break;
            case 0xF0:
                printf("SYSCALL\n");
                instruction_syscall(context);
                break;
            case 0xFF:
                printf("NOOP\n");
                break;
            case 0xFE:
                printf("HALT\n");
                while (1);
                break;
            default:
                printf("WARNING : unknown instruction : 0x%x\n", instruction);
        }
        if (instruction == 0x20 || instruction == 0x21){
            is_last_instruction_cmp = true;
        } else {
            is_last_instruction_cmp = false;
        }
    }
    printf("REGS AT THE END : r0 = %x, r1 = %x, r2 = %x, r3 = %x, r4 = %x\n", context->r0, context->r1, context->r2, context->r3, context->r4);
    printf("REGS AT THE END as ints : r0 = %d, r1 = %d, r2 = %d, r3 = %d, r4 = %d\n", context->r0, context->r1, context->r2, context->r3, context->r4);
    //free(context->code);
    free(context->mem);
    free(context);
    fclose(f);
    return 0;
}