#!bin/bash

clang -Wall \
    -fsanitize=address \
    main.c \
    core/cpu6502.c \
    core/ppu2C02.c \
    core/cartridge.c \
    utils/dyn_array.c \
    core/emulator.c -o build/nes_emu