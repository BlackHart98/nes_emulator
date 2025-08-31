#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "core.h"


int core_emulator_emulate(
    core_main_bus_t *           main_bus
    , core_cpu_t *              cpu
    , core_cpu_register_t *     cpu_register
    , core_ram_t *              cpu_ram
    , core_ppu_t *              ppu
    , core_ppu_bus_t *          ppu_bus
    , core_ppu_register_t *     ppu_register
    , core_name_table_t *       name_table
    , core_pattern_t *          pattern
    , core_program_rom_t *      prgrom
    , core_cartridge_t *        cartridge
){  
    // On create 
    uint32_t nes_system_clock = 0;
    core_cartridge_map_prgrom_chunk(cartridge, prgrom);
    core_cpu6502_reset(cpu, cpu_register, main_bus);


    for(;;){
        printf("----------------------");
        printf("PPU tick.\n");
        // ppu tick
        if ((nes_system_clock % 3) == 0){
            // cpu tick;
            printf("======================");
            printf("CPU tick.\n");
            printf("flags before:\n");
            printf("%x", cpu_register->status);
            printf("\n");
            core_cpu6502_clock(cpu, cpu_register, main_bus);
            printf("Here is the content of the cpu ram:\n");
            printf("flags after:\n");
            printf("%x", cpu_register->status);
            printf("\n");
        }
        nes_system_clock += 1;
        break;
    }
    return 0;
}