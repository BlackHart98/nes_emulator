#include <stdio.h>
#include "core/core.h"
#include "utils/utils.h"

int main(int argc, char * argv[]){
    if (argc != 2){
        printf("Usage: nes_emu <game_file_path>\n");
        return 1;
    }
    char * game_file_name = argv[1];

    core_main_bus_t my_bus = core_bus_init();
    core_cpu_t my_cpu = core_cpu6502_cpu_init();
    core_cpu_register_t my_cpu_register = core_cpu6502_register_init(); // I don't think I needed to separate the register but we'll see
    core_ram_t my_ram = core_ram_init(&my_bus);
    core_ppu_register_t my_ppu_register = core_ppu2C02_register_init(&my_bus); // Same applies to this
    core_ppu_bus_t my_ppu_bus = core_ppu_bus_init();
    core_name_table_t my_name_table = core_name_table_init(&my_ppu_bus);
    core_pattern_t my_pattern = core_pattern_init(&my_ppu_bus);
    core_ppu_t my_ppu = core_ppu2C02_init();
    core_cartridge_t some_cartridge = core_cartridge_init(game_file_name);

    printf("Hello world there, this is the data in the address 0x0 = #%i.\n", my_bus.address_line[0]);

    core_cpu6502_write(&my_bus, 0x0000, 5);
    printf("Here is the address of the bus, #%d\n", my_bus.address_line[0x0000]);
    printf("Here is the address of the ram, #%d\n", my_ram.buffer[0x0000]);

    core_cpu6502_write(&my_bus, (0x2000 + 2), 90);
    printf("Here is the address of the bus, #%d\n", my_bus.address_line[(0x0000)]);
    printf("Here is the address of the ppu register, #%d\n", my_ppu_register.ppu_register[0x0002]);

    // core_emulator_emulate(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    utils_dyn_array_set_index(&some_cartridge.character_memory, 0, 4);

    printf("Here is the value at index = #%d.\n", utils_dyn_array_get_index(&some_cartridge.character_memory, 0));

    core_cartridge_deinit(&some_cartridge);

    // This should segfault, but I abort it before it does
    // printf("Here is the value at index = #%d.\n", utils_dyn_array_get_index(&some_cartridge.character_memory, 0));

    return 0;
}