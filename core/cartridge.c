#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "core.h"
#include "../utils/utils.h"


core_cartridge_t core_cartridge_init(char * file_name){ 
    return (core_cartridge_t){
        .character_memory = utils_dyn_array_init(KB(8)),
        .program_memory = utils_dyn_array_init(KB(8)),
    };
}


void core_cartridge_deinit(core_cartridge_t * cartridge){
    utils_dyn_array_destroy(&cartridge->character_memory);
    utils_dyn_array_destroy(&cartridge->program_memory);
}