#include "lexer.h"
#define _GNU_SOURCE
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "context.h"

#define INSTRUCTION_BUF_SIZE 20

int getCharLine(struct assembler_context* context){
    static char* buffer;
    size_t buf_size;
    if (context->line == NULL){
        context->instruction = malloc(sizeof(char) * INSTRUCTION_BUF_SIZE);
        buf_size = 100;
        buffer = malloc(buf_size * sizeof(char)); // 100 is for now long enough for the max size of a line
        getline(&buffer, &buf_size, context->in_file);
        printf("got line buffer : %s\n", buffer);
        context->line = buffer;
    }
    int c = context->line[context->pos];
    if (c == '\0'){
        printf("\\0 FOUND\n");
        /*while (c == '\0'){
        pos++;
        c = line[pos];
        }
        printf("next char after \\0 : %d\n", line[pos]);*/
        return EOF;
    }
    //printf("c : %c\n", c);
    if (c == '#' || c == '.'){
        while (context->line[context->pos++] != '\n'){}
        c = '\n';
    }
    if (c =='\n'){
        printf("NEW LINE\n");
        context->pos = 0;
        context->line_nb++;
        getline(&buffer, &buf_size, context->in_file);
        context->line = buffer;
        c = getCharLine(context);
        printf("next char after \\n : %d\n", c);
        // TODO goToNextLine
    } else {
        context->pos++;
    }
    //printf("getCharLine returned : %c\n", c);
    return c;
}

int gettok(struct assembler_context* context){
    static int LastChar = ' ';
    while (isspace(LastChar)){
        LastChar = getCharLine(context);
    }
    if (isalpha(LastChar)){
        if (isupper(LastChar)){
            // instruction
            context->pos_instruction = 0;
            memset(context->instruction, 0, INSTRUCTION_BUF_SIZE);
            context->instruction[context->pos_instruction] = LastChar;
            context->pos_instruction++;
            while (isalnum((LastChar = getCharLine(context)))){ // && is_upper ?
                context->instruction[context->pos_instruction] = LastChar;
                context->pos_instruction++;
            }
            printf("instruction %s\n", context->instruction);
            return tok_instruction;
        }
        if (LastChar == 'r'){
            //reg
            char* regNbStr = malloc(10 * sizeof(char));
            int pos_regNbStr = 0;
            do {
                LastChar = getCharLine(context);
                regNbStr[pos_regNbStr] = LastChar;
                printf("adding char to regNb : %d\n", LastChar);
                pos_regNbStr++;
            } while (isdigit(LastChar));
            context->reg_nb = (int)strtol(regNbStr, NULL, 10);
            printf("reg number : %d\n", context->reg_nb);
            return tok_reg;
        }
        // label name
        int label_length = 5;
        char* label_name = malloc(sizeof(char)  * label_length);
        int pos_label = 0;
        do {
            label_name[pos_label] = LastChar;
            pos_label++;
            if (pos_label+1 == label_length){
                label_length += 5;
                label_name = realloc(label_name, sizeof(char) * label_length);
            }
        } while ((isalnum((LastChar = getCharLine(context))) || LastChar == '_') && !isupper(LastChar)); // So labels can't contain uppercase letters TODO ?
        printf("label name : %s\n", label_name);
        context->label_name = label_name;
        return tok_label_name;
    }
    if (isdigit(LastChar)) {
        // number
        // TODO : have a dynamically allocated string that will expand if it is longer than expected
        char* numStr = malloc(25 * sizeof(char));
        int pos_numstr = 0;
        int first_digit = LastChar;
        LastChar = getCharLine(context);
        bool is_hex = false;
        if (first_digit == '0' && LastChar == 'x'){
            LastChar = getCharLine(context);
            is_hex = true;
        } else {
            numStr[pos_numstr] = first_digit;
            pos_numstr++;
        }
        while (isdigit(LastChar)){
            numStr[pos_numstr] = LastChar;
            pos_numstr++;
            LastChar = getCharLine(context);
        }
        // TODO : maybe add a special to int function : https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c to verify if the long is bigger than INT_MAX
        int base = (is_hex) ? 16 : 10;
        int val = (int)strtol(numStr, NULL, base);
        free(numStr);
        if (is_hex){
            context->hex_nb = val;
            return tok_hex;
        } else {
            printf("number : %d\n", val);
            context->number = val;
            return tok_number;
        }
    }
    if (LastChar == EOF){
        return tok_eof;
    }
    printf("LastChar returned : %c (as int : %d)\n", LastChar, LastChar);
    int ThisChar = LastChar;
    LastChar = getCharLine(context);
    return ThisChar;
}

int getNextToken(struct assembler_context* context){
    context->CurTok = gettok(context);
    return context->CurTok;
}