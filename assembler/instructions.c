#include "instructions.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "errors.h"
#include "utils.h"
#include "context.h"


// TODO : functions depending of the type of parsing
//        example instead of generate_noop() and generate_halt(),
//        we would have generate_no_arg(uint8_t instruction) and we would pass 0xFF for noop and 0xFE for halt
void generate_load(struct assembler_context* context){
    getNextToken(context);
    // TODO : put getting the reg with verifying the token in a separate function
    if (context->CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", context->line_nb);
        exit(1);
    }
    int load_instruction = 0X00;
    uint8_t data1 = 0, data2 = 0;
    int reg_temp = context->reg_nb;
    getNextToken(context);
    if (context->CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken(context);
    if (context->CurTok == tok_reg){
        load_instruction = 0x01;
        data1 = 0x00;
        data2 = context->reg_nb;
    } else if (context->CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_hex) {
        // 0x02 instruction
        data1 = uint16_t_low((uint16_t)context->hex_nb);
        data2 = uint16_t_high((uint16_t)context->hex_nb);
    }
    getNextToken(context);
    write_instruction_to_file(context, load_instruction, reg_temp, data1, data2);
}

void generate_add(struct assembler_context* context){
    int instruction_to_write = 0x40;
    getNextToken(context);
    if (context->CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", context->line_nb);
        exit(1);
    }
    int reg_temp = context->reg_nb;
    getNextToken(context);
    if (context->CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken(context);
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        instruction_to_write = 0x40;
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_reg){
        instruction_to_write = 0x42;
        data1 = 0x00;
        data2 = context->reg_nb;
    } else {
        printf("Tok at error : %d\n", context->CurTok);
        error_and_exit(context, "expected a number or a reg in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, reg_temp, data1, data2);
}


// TODO : replace all fprint(stderr, ...) exit(1) with error_and_exit
void generate_sub(struct assembler_context* context){
    int instruction_to_write = 0x41;
    getNextToken(context);
    if (context->CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", context->line_nb);
        exit(1);
    }
    int reg_temp = context->reg_nb;
    getNextToken(context);
    if (context->CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken(context);
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        instruction_to_write = 0x41;
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_reg){
        instruction_to_write = 0x43;
        data1 = 0x00;
        data2 = context->reg_nb;
    } else {
        printf("Tok at error : %d\n", context->CurTok);
        error_and_exit(context, "expected a number or a reg in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, reg_temp, data1, data2);
}

void generate_mul(struct assembler_context* context){
    int instruction_to_write = 0x44;
    getNextToken(context);
    if (context->CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", context->line_nb);
        exit(1);
    }
    int reg_temp = context->reg_nb;
    getNextToken(context);
    if (context->CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken(context);
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        instruction_to_write = 0x44;
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_reg){
        instruction_to_write = 0x46;
        data1 = 0x00;
        data2 = context->reg_nb;
    } else {
        printf("Tok at error : %d\n", context->CurTok);
        error_and_exit(context, "expected a number or a reg in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, reg_temp, data1, data2);
}

void generate_div(struct assembler_context* context){
    int instruction_to_write = 0x45;
    getNextToken(context);
    if (context->CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", context->line_nb);
        exit(1);
    }
    int reg_temp = context->reg_nb;
    getNextToken(context);
    if (context->CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken(context);
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        instruction_to_write = 0x45;
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_reg){
        instruction_to_write = 0x47;
        data1 = 0x00;
        data2 = context->reg_nb;
    } else {
        printf("Tok at error : %d\n", context->CurTok);
        error_and_exit(context, "expected a number or a reg in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, reg_temp, data1, data2);
}

void generate_misc(struct assembler_context* context){
    getNextToken(context);
    uint8_t instruction;
    if (strcmp("NOOP", context->instruction) == 0){
        instruction = 0xFF;
    } else { // HALT
        instruction =  0xFE; 
    }
    write_single_instruction_to_file(context, instruction);
}


// TODO : have only one function for all jumps because the code is very similar
void generate_jmp_always(struct assembler_context* context){
    uint8_t instruction_to_write = 0x33;
    // TODO : replace address with label. Need pre-parsing and hashmap with address = linenumber * 4
    if (context->CurTok != tok_hex){
        error_and_exit(context, "expected an address in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    uint8_t data1 = uint16_t_low((uint16_t)context->hex_nb);
    uint8_t data2 = uint16_t_high((uint16_t)context->hex_nb);
    write_instruction_to_file(context, instruction_to_write, 0, data1, data2);
}

void generate_jmp_equ(struct assembler_context* context){
    uint8_t instruction_to_write = 0x30;
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_hex){
        data1 = uint16_t_low((uint16_t)context->hex_nb);
        data2 = uint16_t_high((uint16_t)context->hex_nb);
    } else if (context->CurTok == tok_label_name){
        int label_address = get_from_label_table(context->label_name, context);
        data1 = uint16_t_low((uint16_t)label_address);
        data2 = uint16_t_high((uint16_t)label_address);
    } else {
        error_and_exit(context, "expected an address or a number in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, 0, data1, data2);
}

void generate_jmp_greater_than(struct assembler_context* context){
    uint8_t instruction_to_write = 0x31;
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_hex){
        data1 = uint16_t_low((uint16_t)context->hex_nb);
        data2 = uint16_t_high((uint16_t)context->hex_nb);
    } else if (context->CurTok == tok_label_name){
        int label_address = get_from_label_table(context->label_name, context);
        data1 = uint16_t_low((uint16_t)label_address);
        data2 = uint16_t_high((uint16_t)label_address);
    } else {
        error_and_exit(context, "expected an address or a number in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, 0, data1, data2);
}

void generate_jmp_lower_than(struct assembler_context* context){
    uint8_t instruction_to_write = 0x32;
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_hex){
        data1 = uint16_t_low((uint16_t)context->hex_nb);
        data2 = uint16_t_high((uint16_t)context->hex_nb);
    } else if (context->CurTok == tok_label_name){
        int label_address = get_from_label_table(context->label_name, context)-8;
        printf("label_address : %d\n", label_address);
        data1 = uint16_t_low((uint16_t)label_address);
        data2 = uint16_t_high((uint16_t)label_address);
    } else {
        error_and_exit(context, "expected an address or a number in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, 0, data1, data2);
}

void generate_jmp(struct assembler_context* context){
    getNextToken(context);
    if (strcmp("JMP", context->instruction) == 0){
        generate_jmp_always(context);
    } else if (strcmp("JEQ", context->instruction) == 0){
        generate_jmp_equ(context);
    } else if (strcmp("JGT", context->instruction) == 0){
        generate_jmp_greater_than(context);
    } else if (strcmp("JLT", context->instruction) == 0){
        generate_jmp_lower_than(context);
    }
}

void generate_cmp(struct assembler_context* context){
    int instruction_to_write = 0;
    getNextToken(context);
    if (context->CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", context->line_nb);
        exit(1);
    }
    int reg_temp = context->reg_nb;
    getNextToken(context);
    if (context->CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken(context);
    uint8_t data1 = 0, data2 = 0;
    if (context->CurTok == tok_number){
        instruction_to_write = 0x21;
        data1 = uint16_t_low((uint16_t)context->number);
        data2 = uint16_t_high((uint16_t)context->number);
    } else if (context->CurTok == tok_reg){
        instruction_to_write = 0x20;
        data1 = 0x00;
        data2 = context->reg_nb;
    } else {
        printf("Tok at error : %d\n", context->CurTok);
        error_and_exit(context, "expected a number or a reg in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    write_instruction_to_file(context, instruction_to_write, reg_temp, data1, data2);
}