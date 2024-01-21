#include "labels.h"
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "context.h"
#include "errors.h"

#define START_SIZE_LABEL_LIST 5

struct label_list* init_label_list(){
    struct label_list* list = malloc(sizeof(struct label_list));
    list->used = 0;
    list->allocated_size = START_SIZE_LABEL_LIST;
    list->label_list = malloc(sizeof(struct label) * list->allocated_size);
    return list;
}

void append_label_list(struct label_list* labels, struct label l){
    if (labels->used == labels->allocated_size){
        labels->allocated_size *= 2;
        labels->label_list = realloc(labels->label_list, labels->allocated_size * sizeof(struct label)); 
    }
    labels->label_list[labels->used++] = l;
}

void destroy_label_list(struct label_list* labels){
    for (int i = 0; i < labels->used; i++){
        free(labels->label_list[i].label_name);
    }
    free(labels->label_list);
    free(labels);
}

#define MAX_SIZE_LINE 4096

void generate_label_table(char* filename, struct assembler_context* context){
    FILE* f = fopen(filename, "r");
    char* line = malloc(MAX_SIZE_LINE * sizeof(char));
    size_t buf_size = MAX_SIZE_LINE;
    int line_nb = 1;
    while (getline(&line, &buf_size, f) != -1){
        if (line[0] != '#'){
            if (line[0] == '.'){
                char* label_name = malloc(sizeof(char) * (buf_size-1));
                strcpy(label_name, line+1);
                label_name[strlen(label_name)-1] = '\0'; // needed to remove the '\n' at the end of the line
                struct label label_temp;
                label_temp.address = line_nb * 4;
                label_temp.label_name = label_name;
                printf("LABEL FOUND at line %d : %s\n", line_nb, label_name);
                append_label_list(context->labels, label_temp);
            } else {
                line_nb++;
            }
        }
    }   
    free(line);
    fclose(f);
}

int get_from_label_table(char* label_name, struct assembler_context* context){
    for (int i = 0; i < context->labels->used; i++){
        if (strcmp(context->labels->label_list[i].label_name, label_name) == 0){
            return context->labels->label_list[i].address;
        }
    }
    error_and_exit(context, "unknown label : %s\n", label_name);
    exit(1);
    return -1;
}