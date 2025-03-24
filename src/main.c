#include <emu.h>

int main(int argc, char *argv[])
{
    if (!emu_init("../ROMs/tests/cpu_instrs/individual/01-special.gb"))
    {
        return 1;
    };

    while (emu_cpu_step())
        ;

    return 0;
}