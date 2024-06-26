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
void instruction_mul_val_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_div_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_mul_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_div_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_cmp_reg_with_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_cmp_reg_with_num(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_and_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_and_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_or_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_or_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_not_of_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_not_of_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_xor_reg_and_val(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_xor_reg_and_reg(struct emulator_context* context, uint8_t reg, uint8_t data1, uint8_t data2);
void instruction_jump(struct emulator_context* context, uint8_t instruction, uint16_t address);
void instruction_syscall(struct emulator_context* context);
void instruction_pop_val(struct emulator_context* context, uint8_t reg);
void instruction_push_val(struct emulator_context* context, uint8_t data1, uint8_t data2);
void instruction_push_val_from_reg(struct emulator_context* context, uint8_t reg);
uint16_t from_2_uint8_t_to_uint16_t(uint8_t u1, uint8_t u2);