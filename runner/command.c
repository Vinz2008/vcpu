#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef WIN32
#include <unistd.h>
#else
#include <io.h>
#define F_OK 0
#define access _access
#endif


static bool file_exists(char* filename){
    if (access(filename, F_OK) == 0) {
        return true;
    } else {
        return false;
    }
}

char* run_asm_command(char* filename){
    char* exe_name = "vcpu-assembler";
    size_t cmd_size = sizeof(char) * (strlen(exe_name) + 1 + strlen(filename));
    char* cmd = malloc(cmd_size);
    if (file_exists("./vcpu-assembler")){
        cmd_size += 2;
        cmd = realloc(cmd, cmd_size);
        exe_name = "./vcpu-assembler";
    }
    sprintf(cmd, "%s %s", exe_name, filename);
    printf("cmd : %s\n", cmd);
    system(cmd);
    free(cmd);
    return "out.bin";
}

void run_emulator_command(char* filename){
    char* exe_name = "vcpu-emulator";
    size_t cmd_size = sizeof(char) * (strlen(exe_name) + 1 + strlen(filename));
    char* cmd = malloc(cmd_size);
    if (file_exists("./vcpu-emulator")){
        cmd_size += 2;
        cmd = realloc(cmd, cmd_size);
        exe_name = "./vcpu-emulator";
    }
    sprintf(cmd, "%s %s", exe_name, filename);
    printf("cmd : %s\n", cmd);
    system(cmd);
    free(cmd);
}