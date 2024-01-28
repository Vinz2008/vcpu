#include "instructions.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "errors.h"
#include "utils.h"
#include "context.h"

/*extern int CurTok;
extern int reg_nb;
extern int number;
extern int hex_nb;

extern int line_nb;

extern FILE* out_file;

extern char* instruction;*/


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
    /*uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = load_instruction;
    buf[1] = reg_temp;
    //uint16_t nb_temp = (uint16_t)number;
    //printf("nb_temp : %d\n", nb_temp);
    buf[2] = data1;
    buf[3] = data2;
    printf("reg nb write : %d %d\n", context->reg_nb, (uint8_t)context->reg_nb);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    debug_print_uint8_buf(buf, BIN_WRITE_BUF_SIZE);
    free(buf);*/
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
    /*uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction_to_write;
    buf[1] = reg_temp;
    buf[2] = data1;
    buf[3] = data2;
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
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
    /*uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction_to_write;
    buf[1] = reg_temp;
    buf[2] = data1;
    buf[3] = data2;
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
}

void generate_misc(struct assembler_context* context){
    getNextToken(context);
    uint8_t instruction;
    //uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    if (strcmp("NOOP", context->instruction) == 0){
        instruction = 0xFF;
    } else { // HALT
        instruction =  0xFE; 
    }
    write_single_instruction_to_file(context, instruction);
    /*memset(buf+1, 0, BIN_WRITE_BUF_SIZE-1);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
}


// TODO : have only one function for all jumps because the code is very similar
void generate_jmp_always(struct assembler_context* context){
    //uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    uint8_t instruction_to_write = 0x33;
    // TODO : replace address with label. Need pre-parsing and hashmap with address = linenumber * 4
    if (context->CurTok != tok_hex){
        error_and_exit(context, "expected an address in instruction %s\n", context->instruction);
    }
    getNextToken(context);
    uint8_t data1 = uint16_t_low((uint16_t)context->hex_nb);
    uint8_t data2 = uint16_t_high((uint16_t)context->hex_nb);
    write_instruction_to_file(context, instruction_to_write, 0, data1, data2);
    
    /*buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
}

void generate_jmp_equ(struct assembler_context* context){
    //uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    //buf[0] = 0x30;
    uint8_t instruction_to_write = 0x30;
    uint8_t data1, data2;
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
    /*buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
}

void generate_jmp_greater_than(struct assembler_context* context){
    //uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    uint8_t instruction_to_write = 0x31;
    uint8_t data1, data2;
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
    /*buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
}

void generate_jmp_lower_than(struct assembler_context* context){
    //uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    uint8_t instruction_to_write = 0x32;
    uint8_t data1, data2;
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
    /*buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
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
    int instruction_to_write;
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
    /*uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction_to_write;
    buf[1] = reg_temp;
    buf[2] = data1;
    buf[3] = data2;
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, context->out_file);
    free(buf);*/
}