#include "context.h"

enum Token {
    tok_eof = -1,
    tok_instruction = -2,
    tok_reg = -3,
    tok_number = -4,
    tok_hex = -5,
    tok_label_name = -6, // change to identifier if there are other identifiers that are not instruction or regs
    tok_unknown = -100,
};

int getNextToken(struct assembler_context* context);