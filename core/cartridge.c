#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "core.h"
#include "../utils/utils.h"

typedef struct _core_cartridge_sheader_t{
    char        name[4];
    uint8_t     prg_rom_chunks;
    uint8_t     chr_rom_chunks;
    uint8_t     mapper1;
    uint8_t     mapper2;
    uint8_t     prg_ram_size;
    uint8_t     tv_system1;
    uint8_t     tv_system2;
    char        unused[5];
} core_cartridge_sheader_t;


core_cartridge_t core_cartridge_init(const char * file_name){ 
    const char * file_name_ = file_name;
    core_cartridge_sheader_t header;
    FILE * fhandle = fopen(file_name_, "rb");
     
    if (fhandle == NULL){
        assert(0&&"File does not exist.");
    }

    fread((char *)&header, sizeof(header), sizeof(header), fhandle);

    

    fclose(fhandle);
    return (core_cartridge_t){
        .character_memory = utils_dyn_array_init(KB(8)),
        .program_memory = utils_dyn_array_init(KB(8)),
    };
}


void core_cartridge_deinit(core_cartridge_t * cartridge){
    utils_dyn_array_destroy(&cartridge->character_memory);
    utils_dyn_array_destroy(&cartridge->program_memory);
}