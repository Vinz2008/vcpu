#include <stddef.h>
#include "context.h"

#ifndef _LABELS_HEADER_
#define _LABELS_HEADER_

struct label {
    char* label_name;
    int address;
};

struct label_list {
    struct label* label_list;
    size_t used;
    size_t allocated_size;
};

struct label_list* init_label_list();
void destroy_label_list(struct label_list* labels);
void generate_label_table(char* filename, struct assembler_context* context);
int get_from_label_table(char* label_name, struct assembler_context* context);

#endif