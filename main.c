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
    core_program_rom_t my_prgrom = core_program_rom_init(&my_bus);


    core_emulator_emulate(
        &my_bus, 
        &my_cpu, 
        &my_cpu_register, 
        &my_ram, 
        &my_ppu, 
        &my_ppu_bus,
        &my_ppu_register, 
        &my_name_table, 
        &my_pattern, 
        &my_prgrom,
        &some_cartridge);


    core_cartridge_deinit(&some_cartridge);
    return 0;
}