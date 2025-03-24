#include <common.h>

enum CPU_REG
{
    CPU_REG_AF,
    CPU_REG_BC,
    CPU_REG_DE,
    CPU_REG_HL,
    CPU_REG_SP,
    CPU_REG_PC
};

enum
{
    CPU_REG_F,
    CPU_REG_A,
    CPU_REG_C,
    CPU_REG_B,
    CPU_REG_E,
    CPU_REG_D,
    CPU_REG_L,
    CPU_REG_H,
};

bool cpu_init(uint8_t header_checksum);

bool cpu_execute(uint16_t inst);

uint16_t cpu_get_double_reg(uint8_t reg);

uint8_t cpu_get_single_reg(uint8_t reg);

void instruction_execute(uint8_t instruction);