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
    , core_cartridge_t *        cartridge
){  
    uint32_t nes_system_clock = 0;

    for(;;){
        printf("----------------------");
        printf("PPU tick.\n");
        // ppu tick
        if ((nes_system_clock % 3) == 0){
            // cpu tick;
            printf("======================");
            printf("CPU tick.\n");
        }
        nes_system_clock += 1;
    }
    return 0;
}