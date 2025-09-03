#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "core.h"


core_ppu_t core_ppu2C02_init(){
    return (core_ppu_t){
        .cycles = 0,
        .scanlines = 0,
        .clock_count = 0,
        .n_chrbanks_id = 0,
    };
}


core_ppu_bus_t core_ppu_bus_init(){
    return (core_ppu_bus_t){
        .address_line = {0},
    };
}


core_ppu_register_t core_ppu2C02_register_init(core_main_bus_t * bus){
    uint8_t * ptr = (uint8_t *)((uintptr_t)bus->address_line + 0x2000);
    return (core_ppu_register_t){
        .ppu_register = ptr,
        .capacity = 0x0008,
    };
}


core_name_table_t core_name_table_init(core_ppu_bus_t * ppu_bus){ 
    return (core_name_table_t){
        .name_table = (uint8_t *)((uintptr_t)ppu_bus->address_line + 0x2000),
        .capacity = KB(2)
    };
}


core_pattern_t core_pattern_init(core_ppu_bus_t * ppu_bus){ 
    return (core_pattern_t){
        .pattern_buffer = ppu_bus->address_line,
        .capacity = KB(8)
    };
}


core_palettes_t core_palettes_init(core_ppu_bus_t * ppu_bus){ 
    return (core_palettes_t){
        .palettes_buffer = (uint8_t *)((uintptr_t)ppu_bus->address_line + 0x3F00),
        .capacity = 0x0020
    };
}


uint8_t core_ppu2C02_read_from_main_bus(core_ppu_register_t * ppu_register, const uint16_t address){
    uint8_t data = 0x00;
    switch (address) {
        case 0x0000:
            break;
        case 0x0001:
            break;
        case 0x0002:
            break;
        case 0x0003:
            break;
        case 0x0004:
            break;
        case 0x0005:
            break;
        case 0x0006:
            break;
        case 0x0007:
            break;
    }
    return data;
}


void core_ppu2C02_write_to_main_bus(core_ppu_register_t * ppu_register, const uint16_t address, const uint8_t data){
    switch (address) {
        case 0x0000:
            break;
        case 0x0001:
            break;
        case 0x0002:
            break;
        case 0x0003:
            break;
        case 0x0004:
            break;
        case 0x0005:
            break;
        case 0x0006:
            break;
        case 0x0007:
            break;
    }
}


uint8_t core_ppu2C02_read_from_ppu_bus(core_ppu_bus_t * ppu_bus, const uint16_t address){
    if (address >= 0x0000 && address <= 0x1FFF){
        return ppu_bus->address_line[address];
    }
    return 0x00;
}


void core_ppu2C02_write_to_ppu_bus(core_ppu_bus_t * ppu_bus, const uint16_t address, const uint8_t data){
    if (address >= 0x0000 && address <= 0x1FFF){
        ppu_bus->address_line[address] = data;
    }
}

bool core_ppu2C02_clock(core_ppu_t * ppu){
    ppu->cycles++;
	if (ppu->cycles >= 341)
	{
		ppu->cycles = 0;
		ppu->scanlines++;
		if (ppu->scanlines >= 261)
		{
			ppu->scanlines = -1;
			return true;
		}
	}
    return false;
}