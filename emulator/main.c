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
    FILE* f = fopen(filename, "rb");
    struct emulator_context* context = malloc(sizeof(struct emulator_context));
    context->code = malloc(sizeof(uint8_t) * 1);
    context->mem = malloc(sizeof(uint8_t) * MEM_SIZE+1);
    context->mem[0xffff] = 3;
    context->is_cmp_true = false;
    int i = 0;
    while (fread(&context->code[i],sizeof(uint8_t), 1, f) > 0){
        //printf("%p\n", context->code[i]);
        context->code = realloc(context->code, sizeof(uint8_t) * (i + 1));
        i++;
    }
    context->code_size = i;
    printf("code size : %d\n", context->code_size);
    /*for (int i = 0; i < context->code_size; i++){
        printf("instruction : %x\n", context->code[i]);
    }*/
    for (int i = 0; i < context->code_size; i += 4){
        uint8_t instruction =  context->code[i];
        uint8_t reg = context->code[i+1];
        uint8_t data1 = context->code[i+2];
        uint8_t data2 = context->code[i+3];
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
                break;
            case 0x21:
                printf("CMP with num\n");
                break;
            default:
                printf("WARNING : unknown instruction : 0x%x\n", instruction);
        }
    }
    printf("REGS AT THE END : r0 = %x, r1 = %x, r2 = %x, r3 = %x, r4 = %x\n", context->r0, context->r1, context->r2, context->r3, context->r4);
    free(context->code);
    free(context->mem);
    free(context);
    fclose(f);
    return 0;
}