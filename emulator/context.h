#include <stdint.h>
#include <stdbool.h>

struct emulator_context {
    //uint8_t* code;
    int code_size;
    uint16_t pc;
    uint16_t r0, r1, r2, r3, r4;
    uint8_t* mem;
    bool cmp_flag;
    bool is_greater_flag;
    bool is_lower_flag;
    // TODO : add the stack, and maybe a screen in a part of memory (probably write it in the specs)
};