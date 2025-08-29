#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "core.h"


// core_cartridge_t core_cartridge_init(core_ppu_bus_t * ppu_bus){ 
//     return (core_cartridge_t){
//         .rom_buffer = (uint8_t *)((uintptr_t)ppu_bus->address_line + 0x4020),
//         .rom_capacity = (0xFFFF - 0x4020),
//     };
// }