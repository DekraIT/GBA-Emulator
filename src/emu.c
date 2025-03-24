#include <emu.h>

bool emu_init(char *file_name)
{
    if (!cart_load(file_name))
    {
        printf("ERROR while loading Cart.");
        exit(1);
    }

    uint16_t cart_checksum = cart_get_checksum();

    if (!cpu_init(cart_checksum))
    {
        printf("ERROR while initializing CPU.");
        exit(1);
    }

    return true;
};

uint8_t read_memory(uint16_t addr)
{
    if (addr <= 0x7FFF)
    {
        return cart_read_byte_at(addr); // TODO return from rom
    }

    if (addr <= 0xDFFF && addr >= 0xC000)
    {
        return ram_read(addr - 0xC000);
    }

    NO_IMPL;
    return 0;
};

bool emu_cpu_step()
{
    uint16_t instruction_addr = cpu_get_double_reg(CPU_REG_PC);

    uint8_t instruction = read_memory(instruction_addr);

    printf("instruction addr %d \n", instruction_addr);
    printf("instruction %d \n", instruction);

    instruction_execute(instruction);

    return true;
};