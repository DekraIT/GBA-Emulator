#include <common.h>
#include <cart.h>
#include <cpu.h>
#include <ram.h>

bool emu_init(char *file_name);

bool emu_cpu_step();

uint8_t read_memory(uint16_t addr);