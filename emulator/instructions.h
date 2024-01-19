#include <stdint.h>

void instruction_load_from_num_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_load_from_mem_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_load_from_reg_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);

void instruction_store_from_reg_to_mem(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_store_from_reg_to_mem_high(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_store_from_reg_to_mem_low(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_add_val_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_add_reg_to_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_sub_val_from_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_sub_reg_from_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
uint16_t from_2_uint8_t_to_uint16_t(uint8_t u1, uint8_t u2);
void instruction_jump(struct emulator_context* context, uint8_t instruction, uint16_t address);