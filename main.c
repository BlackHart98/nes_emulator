#include <stdio.h>
#include "core/core.h"
#include "utils/utils.h"

int main(int argc, char * argv[]){
    if (argc != 2){
        printf("Usage: nes_emu <game_file_path>\n");
        return 1;
    }
    char * game_file_name = argv[1];
    core_emulator_emulate(game_file_name);
    return 0;
}