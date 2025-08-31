#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "core.h"
#include "../utils/utils.h"

typedef struct _core_cartridge_sheader_t{
    char        name[4];
    uint8_t     prgrom_chunks;
    uint8_t     chrrom_chunks;
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

    // read the nes file header
    fread((char *)&header, sizeof(header), 1, fhandle);

    if (header.mapper1 & 0x04){ 
        printf("Got here...\n");
        if (fseek(fhandle, 512, SEEK_CUR) != 0)
            assert(0&&"Could not find trainer.");
    }

    uint8_t n_mapper_id = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);

    if ((header.prgrom_chunks == 0) || (header.chrrom_chunks == 0)){
        assert(0&&"Program ROM chunk or Character Chunks cannot be 0.");
    }

    printf("header.prgrom_chunks: #%d\n", header.prgrom_chunks);

    uint8_t n_filetype = 1;

    if (n_filetype == 0)
    ;

    // Warning this is a TNT!
    utils_dyn_array_t program_memory = utils_dyn_array_init(header.prgrom_chunks * KB(16));
    utils_dyn_array_t character_memory = utils_dyn_array_init(header.chrrom_chunks * KB(8));
    if (n_filetype == 1){
        fread((char *)program_memory.buffer, program_memory.capacity, 1, fhandle);
        fread((char *)character_memory.buffer, character_memory.capacity, 1, fhandle);
    }


    if (n_filetype == 2)
    ;

    fclose(fhandle);
    return (core_cartridge_t){
        .n_chrbanks_id = header.chrrom_chunks,
        .n_mapper_id = n_mapper_id,
        .n_prgbanks_id = header.prgrom_chunks,
        .character_memory = character_memory,
        .program_memory = program_memory,
    };
}


void core_cartridge_deinit(core_cartridge_t * cartridge){
    cartridge->n_chrbanks_id = 0;
    cartridge->n_mapper_id = 0;
    cartridge->n_prgbanks_id = 0;
    utils_dyn_array_destroy(&cartridge->character_memory);
    utils_dyn_array_destroy(&cartridge->program_memory);
}



inline void core_cartridge_map_prgrom_chunk(core_cartridge_t * cartridge, core_program_rom_t * prgrom){
    assert((prgrom != NULL)&&"Program ROM can't be NULL");
    printf("mapping cartridge to program rom window\n");
    switch (cartridge->n_mapper_id){
        case 0: {
            memcpy(prgrom->program_memory, cartridge->program_memory.buffer, prgrom->capacity);
            break;
        }
    }
}

inline void core_cartridge_map_chrrom_chunk(core_cartridge_t * cartridge, core_pattern_t * chrrom){
    assert((chrrom != NULL)&&"Pattern memory can't be NULL");
    printf("mapping cartridge to program rom window\n");
    switch (cartridge->n_mapper_id){
        case 0: {
            memcpy(chrrom->pattern_buffer, cartridge->character_memory.buffer, chrrom->capacity);
            break;
        }
    }
}
