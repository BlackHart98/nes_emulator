#!bin/bash

clang -Wall \
    -O3 \
    main.c \
    core/cpu6502.c \
    core/ppu2C02.c \
    core/cartridge.c \
    utils/dyn_array.c -o build/nes_emu_release