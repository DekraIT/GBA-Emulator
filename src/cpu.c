#include <emu.h>

typedef union
{
    struct
    {
        uint16_t AF;
        uint16_t BC;
        uint16_t DE;
        uint16_t HL;
        uint16_t SP;
        uint16_t PC;
    };
    struct
    {
        uint8_t F;
        uint8_t A;
        uint8_t C;
        uint8_t B;
        uint8_t E;
        uint8_t D;
        uint8_t L;
        uint8_t H;
    };
    uint16_t reg_double[6]; // 16-bit register
    uint8_t reg_single[8];  // 8-bit register
} registers;

registers registers_ctx;

FILE *log_fp;

bool cpu_init(uint8_t header_checksum)
{
    registers_ctx.A = 0x01;
    registers_ctx.F = header_checksum > 0 ? 0b10000000 : 0b10110000;
    registers_ctx.B = 0x00;
    registers_ctx.C = 0x13;
    registers_ctx.D = 0x00;
    registers_ctx.E = 0xD8;
    registers_ctx.H = 0x01;
    registers_ctx.L = 0x4D;
    registers_ctx.PC = 0x0100;
    registers_ctx.SP = 0xFFFE;

    log_fp = fopen("./log.txt", "w+");

    return true;
};

bool cpu_execute(uint16_t inst)
{
}

uint16_t cpu_get_double_reg(uint8_t reg)
{
    return registers_ctx.reg_double[reg];
};

uint8_t cpu_get_single_reg(uint8_t reg)
{
    return registers_ctx.reg_single[reg];
};

struct instruction
{
    uint8_t opcpde;
    uint8_t t_cycle;
    void (*function)(uint8_t opcode);
    uint8_t m_cycle;
};

void no_impl(uint8_t opcode)
{
    printf("Unknown Opcode: %02X  \n", opcode);
    exit(1);
};

void instr_no_op(uint8_t opcode)
{
    return;
};

enum CPU_REG instr_incr_16_look_up[4] = {
    CPU_REG_BC,
    CPU_REG_DE,
    CPU_REG_HL,
    CPU_REG_SP,
};

void instr_incr_8(uint8_t opcode)
{
    uint8_t reg_index = opcode >> 4 & 0b00000011;

    uint8_t result, carry_per_bit = registers_ctx.reg_double[instr_incr_16_look_up[reg_index]]++;

    printf("%");

    BIT_SET(registers_ctx.F, 7, result == 0);
    BIT_SET(registers_ctx.F, 6, 0);
    BIT_SET(registers_ctx.F, 5, carry_per_bit >> 3 & 0b00000001);
};

void instr_incr_16(uint8_t opcode)
{
    uint8_t reg_index = opcode >> 4 & 0b00000011;

    registers_ctx.reg_double[instr_incr_16_look_up[reg_index]]++;
};

void instr_decr_8(uint8_t opcode)
{
    uint8_t reg_index = opcode >> 4 & 0b00000011;

    registers_ctx.reg_double[instr_incr_16_look_up[reg_index]]--;
};

void instr_decr_16(uint8_t opcode)
{
    uint8_t reg_index = opcode >> 4 & 0b00000011;

    registers_ctx.reg_double[instr_incr_16_look_up[reg_index]]--;
};

typedef void (*function)(uint8_t opcode);

// TODO: check the INC (HL) and DEV (HL) Opcode, since need to read the content on adress HL first from RAM

// clang-format off
function instructions[256] = {
    instr_no_op, no_impl, no_impl, instr_incr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, instr_decr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, instr_incr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, instr_decr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, instr_incr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, instr_decr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, instr_incr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, instr_decr_16, instr_incr_8, instr_decr_8, no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
    no_impl,     no_impl, no_impl, no_impl,       no_impl,      no_impl,      no_impl, no_impl,
 };
// clang-format on

void instruction_execute(uint8_t instruction)
{

    printf("A:%02X F:%02X B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X SP:%04X PC:%04X PCMEM:%02X,%02X,%02X,%02X\n",
           registers_ctx.A, registers_ctx.F, registers_ctx.B, registers_ctx.C, registers_ctx.D, registers_ctx.E, registers_ctx.H, registers_ctx.L, registers_ctx.SP, registers_ctx.PC, read_memory(registers_ctx.PC), read_memory(registers_ctx.PC + 1), read_memory(registers_ctx.PC + 2), read_memory(registers_ctx.PC + 3));

    fprintf(log_fp, "A:%02X F:%02X B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X SP:%04X PC:%04X PCMEM:%02X,%02X,%02X,%02X\n",
            registers_ctx.A, registers_ctx.F, registers_ctx.B, registers_ctx.C, registers_ctx.D, registers_ctx.E, registers_ctx.H, registers_ctx.L, registers_ctx.SP, registers_ctx.PC, read_memory(registers_ctx.PC), read_memory(registers_ctx.PC + 1), read_memory(registers_ctx.PC + 2), read_memory(registers_ctx.PC + 3));

    instructions[instruction](instruction);

    registers_ctx.PC++;
};
