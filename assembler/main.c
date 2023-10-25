#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lexer.h"
#include "instructions.h"
#include "errors.h"

#define BIN_WRITE_BUF_SIZE 4

FILE* in_file;

FILE* out_file;

extern int line_nb;

extern int reg_nb;

extern int CurTok;
extern char* instruction;


extern int number;

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

void mainLoop(){
    getNextToken();
    while (true){
    //getNextToken();
    printf("instruction_tok : %d\n", CurTok);
    if (CurTok == tok_eof){
        break;
    }
    if (CurTok != tok_instruction){
        fprintf(stderr, "expected instruction at the start of the line %d\n", line_nb);
        exit(1);
    }
    if (strcmp("LOAD", instruction) == 0){
        //generate_load();
        getNextToken();
        //generate_load();
        // TODO : put getting the reg with verifying the token in a separate function
        if (CurTok != tok_reg){
            fprintf(stderr, "expected register after load instruction in line %d\n", line_nb);
            exit(1);
        }
        int load_instruction = 0X00;
        uint8_t data1, data2;
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
        free(buf);
    } else if (strcmp("NOOP", instruction) == 0 || strcmp("HALT", instruction) == 0){
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
    } else if (strcmp("ADD", instruction) == 0){
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
    } else if (strcmp("SUB", instruction) == 0){
        
    }
    }
    /*while (getNextToken() != tok_unknown && CurTok != '\0'){
        printf("CurTok : %d\n", CurTok);
    }*/
    //printf("exiting mainloop\n");
    return;
}

int main(int argc, char** argv){
    if (argc < 2){
        printf("missing file for emulator\n");
        exit(1);
    }
    char* filename = NULL;
    char* output_filename = "out.bin";
    for (int i = 0; i < argc; i++){
        if (strcmp("-o", argv[i]) == 0){
            i++;
            output_filename = argv[i];
        } else {
            filename = argv[i];
        }
    }
    if (!filename){
        printf("missing file for emulator\n");
        exit(1);
    }
    in_file = fopen(filename, "r");
    out_file = fopen(output_filename, "wb");
    mainLoop();
    fclose(in_file);
}