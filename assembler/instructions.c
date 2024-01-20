#include "instructions.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "errors.h"
#include "utils.h"

extern int CurTok;
extern int reg_nb;
extern int number;
extern int hex_nb;

extern int line_nb;

extern FILE* out_file;

extern char* instruction;

// TODO move every generated instructions in its own function
// TODO : functions depending of the type of parsing
//        example instead of generate_noop() and generate_halt(),
//        we would have generate_no_arg(uint8_t instruction) and we would pass 0xFF for noop and 0xFE for halt
void generate_load(){
    getNextToken();
    // TODO : put getting the reg with verifying the token in a separate function
    if (CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", line_nb);
        exit(1);
    }
    int load_instruction = 0X00;
    uint8_t data1 = 0, data2 = 0;
    int reg_temp = reg_nb;
    getNextToken();
    if (CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken();
    if (CurTok == tok_reg){
        load_instruction = 0x01;
        data1 = 0x00;
        data2 = reg_nb;
    } else if (CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)number);
        data2 = uint16_t_high((uint16_t)number);
    } else if (CurTok == tok_hex) {
        // 0x02 instruction
        data1 = uint16_t_low((uint16_t)hex_nb);
        data2 = uint16_t_high((uint16_t)hex_nb);
    }
    getNextToken();
    // 0X00 instruction
    // TODO : create a function which allocates the buffer and fill it
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = load_instruction;
    buf[1] = reg_temp;
    //uint16_t nb_temp = (uint16_t)number;
    //printf("nb_temp : %d\n", nb_temp);
    buf[2] = data1;
    buf[3] = data2;
    printf("reg nb write : %d %d\n", reg_nb, (uint8_t)reg_nb);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    debug_print_uint8_buf(buf, BIN_WRITE_BUF_SIZE);
    free(buf);
}

void generate_add(){
    int instruction_to_write = 0x40;
    getNextToken();
    if (CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", line_nb);
        exit(1);
    }
    int reg_temp = reg_nb;
    getNextToken();
    if (CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken();
    uint8_t data1 = 0, data2 = 0;
    if (CurTok == tok_number){
        instruction_to_write = 0x40;
        data1 = uint16_t_low((uint16_t)number);
        data2 = uint16_t_high((uint16_t)number);
    } else if (CurTok == tok_reg){
        instruction_to_write = 0x42;
        data1 = 0x00;
        data2 = reg_nb;
    } else {
        printf("Tok at error : %d\n", CurTok);
        error_and_exit("expected a number or a reg in instruction %s\n", instruction);
    }
    getNextToken();
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction_to_write;
    buf[1] = reg_temp;
    buf[2] = data1;
    buf[3] = data2;
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}


// TODO : replace all fprint(stderr, ...) exit(1) with error_and_exit
void generate_sub(){
    int instruction_to_write = 0x41;
    getNextToken();
    if (CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", line_nb);
        exit(1);
    }
    int reg_temp = reg_nb;
    getNextToken();
    if (CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken();
    uint8_t data1 = 0, data2 = 0;
    if (CurTok == tok_number){
        instruction_to_write = 0x41;
        data1 = uint16_t_low((uint16_t)number);
        data2 = uint16_t_high((uint16_t)number);
    } else if (CurTok == tok_reg){
        instruction_to_write = 0x43;
        data1 = 0x00;
        data2 = reg_nb;
    } else {
        printf("Tok at error : %d\n", CurTok);
        error_and_exit("expected a number or a reg in instruction %s\n", instruction);
    }
    getNextToken();
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction_to_write;
    buf[1] = reg_temp;
    buf[2] = data1;
    buf[3] = data2;
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}

void generate_misc(){
    getNextToken();
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    if (strcmp("NOOP", instruction) == 0){
        buf[0] = 0xFF;
    } else { // HALT
        buf[0] = 0xFE; 
    }
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-1);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}


// TODO : have only one function for all jumps because the code is very similar
void generate_jmp_always(){
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = 0x33;
    // TODO : replace address with label. Need pre-parsing and hashmap with address = linenumber * 4
    if (CurTok != tok_hex){
        error_and_exit("expected an address in instruction %s\n", instruction);
    }
    getNextToken();
    uint8_t data1 = uint16_t_low((uint16_t)hex_nb);
    uint8_t data2 = uint16_t_high((uint16_t)hex_nb);
    buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}

void generate_jmp_equ(){
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = 0x30;
    uint8_t data1, data2;
    if (CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)number);
        data2 = uint16_t_high((uint16_t)number);
    } else if (CurTok == tok_hex){
        data1 = uint16_t_low((uint16_t)hex_nb);
        data2 = uint16_t_high((uint16_t)hex_nb);
    } else {
        error_and_exit("expected an address or a number in instruction %s\n", instruction);
    }
    getNextToken();
    buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}

void generate_jmp_greater_than(){
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = 0x31;
    uint8_t data1, data2;
    if (CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)number);
        data2 = uint16_t_high((uint16_t)number);
    } else if (CurTok == tok_hex){
        data1 = uint16_t_low((uint16_t)hex_nb);
        data2 = uint16_t_high((uint16_t)hex_nb);
    } else {
        error_and_exit("expected an address or a number in instruction %s\n", instruction);
    }
    getNextToken();
    buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}

void generate_jmp_lower_than(){
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = 0x32;
    uint8_t data1, data2;
    if (CurTok == tok_number){
        data1 = uint16_t_low((uint16_t)number);
        data2 = uint16_t_high((uint16_t)number);
    } else if (CurTok == tok_hex){
        data1 = uint16_t_low((uint16_t)hex_nb);
        data2 = uint16_t_high((uint16_t)hex_nb);
    } else {
        error_and_exit("expected an address or a number in instruction %s\n", instruction);
    }
    getNextToken();
    buf[2] = data1;
    buf[3] = data2;
    memset(buf+1, 0, BIN_WRITE_BUF_SIZE-3);
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}

void generate_jmp(){
    getNextToken();
    if (strcmp("JMP", instruction) == 0){
        generate_jmp_always();
    } else if (strcmp("JEQ", instruction) == 0){
        generate_jmp_equ();
    } else if (strcmp("JGT", instruction) == 0){
        generate_jmp_greater_than();
    } else if (strcmp("JLT", instruction) == 0){
        generate_jmp_lower_than();
    }
}

void generate_cmp(){
    int instruction_to_write;
    getNextToken();
    if (CurTok != tok_reg){
        fprintf(stderr, "expected register after load instruction in line %d\n", line_nb);
        exit(1);
    }
    int reg_temp = reg_nb;
    getNextToken();
    if (CurTok != ','){
        fprintf(stderr, "missing \',\' between values\n");
        exit(1);
    }
    getNextToken();
    uint8_t data1 = 0, data2 = 0;
    if (CurTok == tok_number){
        instruction_to_write = 0x21;
        data1 = uint16_t_low((uint16_t)number);
        data2 = uint16_t_high((uint16_t)number);
    } else if (CurTok == tok_reg){
        instruction_to_write = 0x20;
        data1 = 0x00;
        data2 = reg_nb;
    } else {
        printf("Tok at error : %d\n", CurTok);
        error_and_exit("expected a number or a reg in instruction %s\n", instruction);
    }
    getNextToken();
    uint8_t* buf = malloc(sizeof(uint8_t) * BIN_WRITE_BUF_SIZE);
    buf[0] = instruction_to_write;
    buf[1] = reg_temp;
    buf[2] = data1;
    buf[3] = data2;
    fwrite(buf, 1, BIN_WRITE_BUF_SIZE, out_file);
    free(buf);
}