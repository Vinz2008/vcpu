#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lexer.h"
#include "instructions.h"
#include "errors.h"
#include "utils.h"


// TODO : create a context struct with the line number, the number, the instruction and the file pointers (and which will be passed to all functions ?)
FILE* in_file;

FILE* out_file;

extern int line_nb;

extern int reg_nb;

extern int CurTok;
extern char* instruction;

extern int number;

extern char* line;

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
        //getNextToken();
        generate_load();
    } else if (strcmp("NOOP", instruction) == 0 || strcmp("HALT", instruction) == 0){
        //getNextToken();
        generate_misc();
    } else if (strcmp("ADD", instruction) == 0){
        generate_add();
    } else if (strcmp("SUB", instruction) == 0){
        generate_sub();
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
    free(instruction);
    free(line);
    fclose(in_file);
    fclose(out_file);
}