#include <stdio.h>

#ifndef _ASSEMBLER_CONTEXT_

#define _ASSEMBLER_CONTEXT_

struct assembler_context {
    struct label_list* labels;
    int reg_nb;
    int hex_nb;
    int CurTok;
    char* instruction;
    int pos_instruction;
    int number;
    char* label_name;
    char* line;
    int pos;
    int line_nb;
    FILE* in_file;
    FILE* out_file;
};

#endif