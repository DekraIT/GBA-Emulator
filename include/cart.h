#include <common.h>

bool cart_load(char *file_name);

char *cart_get_title();

uint8_t cart_read_byte_at(uint32_t addr);

void card_write_byte_at(uint32_t addr, uint8_t value);

uint16_t cart_get_checksum();