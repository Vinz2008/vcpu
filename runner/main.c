#include <stdio.h>
#include <stdlib.h>
#include "command.h"

int main(int argc, char** argv){
    char* filename = NULL;
    if (argc < 2){
        printf("missing filename\n");
        exit(1);
    }
    for (int i = 0; i < argc; i++){
        filename = argv[i];
    }
    char* out_filename = run_asm_command(filename);
    run_emulator_command(out_filename);
    remove(out_filename);
    return 0;
}