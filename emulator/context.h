#include <stdint.h>
#include <stdbool.h>

struct emulator_context {
    uint8_t* code;
    int code_size;
    uint16_t pc;
    uint16_t r0, r1, r2, r3, r4;
    uint16_t* mem;
    bool is_cmp_true;
    // TODO : add the stack, and maybe a screen in a part of memory (probably write it in the specs)
};