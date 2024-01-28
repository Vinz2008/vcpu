#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lexer.h"
#include "instructions.h"
#include "errors.h"
#include "utils.h"
#include "context.h"


// TODO : create a context struct with the line number, the number, the instruction and the file pointers (and which will be passed to all functions ?)
/*FILE* in_file;

FILE* out_file;*/

/*extern int line_nb;

extern int reg_nb;

extern int CurTok;
extern char* instruction;

extern int number;

extern char* line;*/

void mainLoop(struct assembler_context* context){
    getNextToken(context);
    while (true){
    //getNextToken();
    printf("instruction_tok : %d\n", context->CurTok);
    if (context->CurTok == tok_eof){
        break;
    }
    if (context->CurTok != tok_instruction){
        fprintf(stderr, "expected instruction at the start of the line %d\n", context->line_nb);
        exit(1);
    }
    if (strcmp("LOAD", context->instruction) == 0){
        //getNextToken();
        generate_load(context);
    } else if (strcmp("NOOP", context->instruction) == 0 || strcmp("HALT", context->instruction) == 0){
        //getNextToken();
        generate_misc(context);
    } else if (strcmp("ADD", context->instruction) == 0){
        generate_add(context);
    } else if (strcmp("SUB", context->instruction) == 0){
        generate_sub(context);
    } else if (strcmp("MUL", context->instruction) == 0){
        generate_mul(context);
    } else if (strcmp("DIV", context->instruction) == 0){
        generate_div(context);
    } else if (strcmp("CMP", context->instruction) == 0){
        generate_cmp(context);
    } else if (context->instruction[0] == 'J'){
        generate_jmp(context);
    } else {
        printf("ERROR : Unknown instruction : %s\n", context->instruction);
        exit(1);
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
    struct assembler_context* context = malloc(sizeof(struct assembler_context));
    context->labels = init_label_list();
    generate_label_table(filename, context);
    context->in_file = fopen(filename, "r");
    context->out_file = fopen(output_filename, "wb");
    context->line = NULL;
    context->line_nb = 1;
    context->pos = 0;
    context->instruction = NULL;
    context->pos_instruction = 0;
    mainLoop(context);
    free(context->instruction);
    free(context->line);
    fclose(context->in_file);
    fclose(context->out_file);
    free(context);
}