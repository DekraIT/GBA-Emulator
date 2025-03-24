#include <emu.h>

uint8_t ram_ctx[0x2000];

uint8_t ram_read(uint16_t adress)
{

    return ram_ctx[adress];
};

void ram_write(uint16_t adress, uint8_t value)
{

    ram_ctx[adress] = value;
};