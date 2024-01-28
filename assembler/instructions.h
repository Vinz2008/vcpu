#include "context.h"

void generate_load(struct assembler_context* context);
void generate_misc(struct assembler_context* context);
void generate_add(struct assembler_context* context);
void generate_sub(struct assembler_context* context);
void generate_mul(struct assembler_context* context);
void generate_div(struct assembler_context* context);
void generate_jmp(struct assembler_context* context);
void generate_cmp(struct assembler_context* context);