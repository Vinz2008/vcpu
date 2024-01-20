#include "lexer.h"
#define _GNU_SOURCE
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* line = NULL;
int pos = 0;

int reg_nb;

#define INSTRUCTION_BUF_SIZE 20
char* instruction;
int pos_instruction = 0;

int number;

int hex_nb;

int CurTok;

int line_nb = 1;

extern FILE* in_file;

int getCharLine(){
    static char* buffer;
    size_t buf_size;
    if (line == NULL){
        instruction = malloc(sizeof(char) * INSTRUCTION_BUF_SIZE);
        buf_size = 100;
        buffer = malloc(buf_size * sizeof(char)); // 100 is for now long enough for the max size of a line
        //memset(buffer, 0, INSTRUCTION_BUF_SIZE);
        getline(&buffer, &buf_size, in_file);
        printf("got line buffer : %s\n", buffer);
        line = buffer;
    }
    int c = line[pos];
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
    if (c == '#'){
        //pos++;
        while (line[pos++] != '\n'){}
        //pos++;
        /*c = getCharLine();
        printf("char after comment : %c %d\n", c);*/
        c = '\n';
    }
    if (c =='\n'){
        printf("NEW LINE\n");
        pos=0;
        line_nb++;
        //memset(buffer, 0, INSTRUCTION_BUF_SIZE);
        getline(&buffer, &buf_size, in_file);
        line = buffer;
        //c = line[pos];
        //pos++;
        c = getCharLine();
        printf("next char after \\n : %d\n", c);
        // TODO goToNextLine
    } else {
        pos++;
    }
    //printf("getCharLine returned : %c\n", c);
    return c;
}

int gettok(){
    static int LastChar = ' ';
    while (isspace(LastChar)){
        LastChar = getCharLine();
    }
    if (isalpha(LastChar)){
        if (isupper(LastChar)){
            // instruction
            pos_instruction = 0;
            memset(instruction, 0, INSTRUCTION_BUF_SIZE);
            instruction[pos_instruction] = LastChar;
            pos_instruction++;
            while (isalnum((LastChar = getCharLine()))){ // && is_upper ?
                instruction[pos_instruction] = LastChar;
                pos_instruction++;
            }
            printf("instruction %s\n", instruction);
            return tok_instruction;
        }
        if (LastChar == 'r'){
            //reg
            LastChar = getCharLine();
            if (!isdigit(LastChar)){
                // TODO : create a error and exit function
                fprintf(stderr, "reg number is not valid");
                exit(1);
            }            
            reg_nb = -('0' - LastChar);
            printf("reg number : %d\n", reg_nb);
            LastChar = getCharLine();
            return tok_reg;
        }
    }
    if (isdigit(LastChar)) {
        // number
        // TODO : have a dynamically allocated string that will expand if it is longer than expected
        char* numStr = malloc(25 * sizeof(char));
        int pos_numstr = 0;
        int first_digit = LastChar;
        LastChar = getCharLine();
        bool is_hex = false;
        if (first_digit == '0' && LastChar == 'x'){
            LastChar = getCharLine();
            is_hex = true;
        } else {
            numStr[pos_numstr] = first_digit;
            pos_numstr++;
        }
        while (isdigit(LastChar)){
            numStr[pos_numstr] = LastChar;
            pos_numstr++;
            LastChar = getCharLine();
        }
        /*do {
            numStr[pos_numstr] = LastChar;
            pos_numstr++;
            LastChar = getCharLine();
        } while (isdigit(LastChar));*/
        // TODO : maybe add a special to int function : https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c to verify if the long is bigger than INT_MAX
        int base = (is_hex) ? 16 : 10;
        int val = (int)strtol(numStr, NULL, base);
        free(numStr);
        if (is_hex){
            hex_nb = val;
            return tok_hex;
        } else {
            printf("number : %d\n", val);
            number = val;
            return tok_number;
        }
    }
    if (LastChar == EOF){
        return tok_eof;
    }
    printf("LastChar returned : %c (as int : %d)\n", LastChar, LastChar);
    int ThisChar = LastChar;
    LastChar = getCharLine();
    return ThisChar;
}

int getNextToken(){
    CurTok = gettok();
    return CurTok;
}