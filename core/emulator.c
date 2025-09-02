#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "core.h"


// Still working with the happy path
int core_emulator_emulate(char * game_file_path){
    // Initialize the NES components  
    core_main_bus_t main_bus = core_bus_init();
    core_cpu_t cpu = core_cpu6502_cpu_init();
    core_cpu_register_t cpu_register = core_cpu6502_register_init(); // I don't think I needed to separate the register but we'll see
    core_ram_t cpu_ram = core_ram_init(&main_bus);
    core_ppu_register_t ppu_register = core_ppu2C02_register_init(&main_bus); // Same applies to this
    core_ppu_bus_t ppu_bus = core_ppu_bus_init();
    core_name_table_t name_table = core_name_table_init(&ppu_bus);
    core_pattern_t pattern = core_pattern_init(&ppu_bus);
    core_ppu_t ppu = core_ppu2C02_init();
    core_cartridge_t cartridge = core_cartridge_init(game_file_path);
    core_program_rom_t prgrom = core_program_rom_init(&main_bus);

    // On create 
    uint32_t nes_system_clock = 0;
    core_cartridge_map_prgrom_chunk(&cartridge, &cpu, &prgrom);
    core_cartridge_map_chrrom_chunk(&cartridge, &ppu, &pattern);

    for(;;){
        printf("----------------------\n");
        printf("PPU tick.\n");
        core_ppu2C02_clock(&ppu);
        // ppu tick
        if ((nes_system_clock % 3) == 0){
            // cpu tick;
            printf("======================\n");
            printf("CPU tick.\n");
            core_cpu6502_clock(&cpu, &cpu_register, &main_bus, 0x8000); // read in the program on the cartridge
        }
        nes_system_clock += 1;
        if (nes_system_clock >= 28)
            break;
    }
    core_cartridge_deinit(&cartridge);
    return 0;
}