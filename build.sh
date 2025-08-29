#!bin/bash

clang -Wall main.c core/cpu6502.c core/ppu2C02.c -o build/nes_emu