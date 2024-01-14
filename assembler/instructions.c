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
    } else if (0) { // TODO add tok_address
        // 0x02 instruction
    }
    getNextToken();
    // 0X00 instruction
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
    uint8_t data1, data2;
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
    uint8_t data1, data2;
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