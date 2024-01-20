enum Token {
    tok_eof = -1,
    tok_instruction = -2,
    tok_reg = -3,
    tok_number = -4,
    tok_hex = -5,
    tok_unknown = -100,
};

int getNextToken();