#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#if defined(_WIN32)
    #define OS_WINDOWS
    #include <windows.h>
#elif defined(__APPLE__) || defined(__linux__)
    #define OS_UNIX_LIKE
    #include <unistd.h>
#endif

#include "core.h"

#define SECOND_PER_FRAME (1.0f / 60.0f)
#define DEFAULT_COEFFICIENT 1.0f


#if defined(OS_UNIX_LIKE)
static inline useconds_t core_emulator_interval(float);

useconds_t core_emulator_interval(float coeff){
    return (useconds_t)(coeff * SECOND_PER_FRAME * 1000000);
}
#elif defined(OS_WINDOWS)
static inline int core_emulator_interval(float);

int core_emulator_interval(float coeff){
    return (int)(coeff * SECOND_PER_FRAME * 1000);
}
#endif


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

    core_cpu6502_reset(&cpu, &cpu_register, &main_bus);

    float elapsed_time = 0.0f;
    bool frame_completed = false;
    float framecount__ = 0.0f;
    float number_of_frames = 0.0f;
    
    for(;;){
        printf("rendering frame...\n");
        do{
            // ppu tick
            frame_completed = core_ppu2C02_clock(&ppu);
            if ((nes_system_clock % 3) == 0){
                // cpu tick;
                core_cpu6502_clock(&cpu, &cpu_register, &main_bus, 0x8000); // read in the program on the cartridge
            }
            nes_system_clock += 1;
        } while(!frame_completed);
        if (frame_completed) {
#if defined(OS_UNIX_LIKE)
            printf("done rendering frame, sleeping for %.4f secs\n", (float)core_emulator_interval(DEFAULT_COEFFICIENT)/1000000);
#endif
            number_of_frames += 1;
            framecount__ += core_emulator_interval(DEFAULT_COEFFICIENT);
            if (number_of_frames == 60.0f){
#if defined(OS_UNIX_LIKE)
                printf("Expected time #~%f actual output #~%f\n", DEFAULT_COEFFICIENT, (float)framecount__/1000000);
#endif
                break;
            }
        }
#if defined(OS_UNIX_LIKE)
        usleep(core_emulator_interval(DEFAULT_COEFFICIENT));
#elif defined(OS_WINDOWS)
        Sleep(core_emulator_interval(DEFAULT_COEFFICIENT)); // this is in millisecs
#endif
        frame_completed = false;
    }
    core_cartridge_deinit(&cartridge);
    return 0;
}