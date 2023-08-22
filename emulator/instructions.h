#include <stdint.h>

void instruction_load_from_num_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_load_from_mem_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_load_from_reg_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);

void instruction_store_from_reg_to_mem(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_store_from_reg_to_mem_high(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_store_from_reg_to_mem_low(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);