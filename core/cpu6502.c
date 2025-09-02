#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "core.h"


// CPU 6502 instruction set arranged in numerical order
// --------------------------------
const core_instruction_t core_lookup[LOOKUP_TABLE_SIZE] = {
    {.instruction_code = BRK, .address_mode = IMP, .cycles = 7}, {.instruction_code = ORA, .address_mode = IDX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 3}, {.instruction_code = ORA, .address_mode = ZP0, .cycles = 3}, {.instruction_code = ASL, .address_mode = ZP0, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = PHP, .address_mode = IMP, .cycles = 3}, {.instruction_code = ORA, .address_mode = IMM, .cycles = 2}, {.instruction_code = ASL, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = ORA, .address_mode = ABS, .cycles = 4}, {.instruction_code = ASL, .address_mode = ABS, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = BPL, .address_mode = REL, .cycles = 2}, {.instruction_code = ORA, .address_mode = IDY, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = ORA, .address_mode = ZPX, .cycles = 4}, {.instruction_code = ASL, .address_mode = ZPX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = CLC, .address_mode = IMP, .cycles = 2}, {.instruction_code = ORA, .address_mode = ABY, .cycles = 4}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = ORA, .address_mode = ABX, .cycles = 7}, {.instruction_code = ASL, .address_mode = IMP, .cycles = 7}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = JSR, .address_mode = ABS, .cycles = 6}, {.instruction_code = AND, .address_mode = IDX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = BIT, .address_mode = ZP0, .cycles = 3}, {.instruction_code = AND, .address_mode = ZP0, .cycles = 3}, {.instruction_code = ROL, .address_mode = ZP0, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = PLP, .address_mode = IMP, .cycles = 4}, {.instruction_code = AND, .address_mode = IMM, .cycles = 2}, {.instruction_code = ROL, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = BIT, .address_mode = ABS, .cycles = 4}, {.instruction_code = AND, .address_mode = ABS, .cycles = 4}, {.instruction_code = ROL, .address_mode = ABS, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = BMI, .address_mode = REL, .cycles = 2}, {.instruction_code = AND, .address_mode = IDY, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = AND, .address_mode = ZPX, .cycles = 4}, {.instruction_code = ROL, .address_mode = ZPX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = SEC, .address_mode = IMP, .cycles = 2}, {.instruction_code = AND, .address_mode = ABY, .cycles = 4}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = AND, .address_mode = ABX, .cycles = 4}, {.instruction_code = ROL, .address_mode = ABX, .cycles = 7}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = RTI, .address_mode = IMP, .cycles = 6}, {.instruction_code = EOR, .address_mode = IDX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 3}, {.instruction_code = EOR, .address_mode = ZP0, .cycles = 3}, {.instruction_code = LSR, .address_mode = IMP, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = PHA, .address_mode = IMP, .cycles = 3}, {.instruction_code = EOR, .address_mode = IMM, .cycles = 2}, {.instruction_code = LSR, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = JMP, .address_mode = ABS, .cycles = 3}, {.instruction_code = EOR, .address_mode = ABS, .cycles = 4}, {.instruction_code = LSR, .address_mode = ABS, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = BVC, .address_mode = REL, .cycles = 2}, {.instruction_code = EOR, .address_mode = IDY, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = EOR, .address_mode = ZPX, .cycles = 4}, {.instruction_code = LSR, .address_mode = ZPX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = CLI, .address_mode = IMP, .cycles = 2}, {.instruction_code = EOR, .address_mode = ABY, .cycles = 4}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = EOR, .address_mode = ABX, .cycles = 4}, {.instruction_code = LSR, .address_mode = ABX, .cycles = 7}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = RTS, .address_mode = IMP, .cycles = 6}, {.instruction_code = ADC, .address_mode = IDX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 3}, {.instruction_code = ADC, .address_mode = ZP0, .cycles = 3}, {.instruction_code = ROR, .address_mode = ZP0, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = PLA, .address_mode = IMP, .cycles = 4}, {.instruction_code = ADC, .address_mode = IMM, .cycles = 2}, {.instruction_code = ROR, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = JMP, .address_mode = IND, .cycles = 5}, {.instruction_code = ADC, .address_mode = ABS, .cycles = 4}, {.instruction_code = ROR, .address_mode = ABS, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = BVS, .address_mode = REL, .cycles = 2}, {.instruction_code = ADC, .address_mode = IDY, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = ADC, .address_mode = ZPX, .cycles = 4}, {.instruction_code = ROR, .address_mode = ZPX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = SEI, .address_mode = IMP, .cycles = 2}, {.instruction_code = ADC, .address_mode = ABY, .cycles = 4}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = ADC, .address_mode = ABX, .cycles = 4}, {.instruction_code = ROR, .address_mode = ABX, .cycles = 7}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = STA, .address_mode = IDX, .cycles = 6}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = STY, .address_mode = ZP0, .cycles = 3}, {.instruction_code = STA, .address_mode = ZP0, .cycles = 3}, {.instruction_code = STX, .address_mode = ZP0, .cycles = 3}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 3}, 
    {.instruction_code = DEY, .address_mode = IMP, .cycles = 2}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = TXA, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = STY, .address_mode = ABS, .cycles = 4}, {.instruction_code = STA, .address_mode = ABS, .cycles = 4}, {.instruction_code = STX, .address_mode = ABS, .cycles = 4}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 4}, 
    {.instruction_code = BCC, .address_mode = REL, .cycles = 2}, {.instruction_code = STA, .address_mode = IDY, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = STY, .address_mode = ZPX, .cycles = 4}, {.instruction_code = STA, .address_mode = ZPX, .cycles = 4}, {.instruction_code = STX, .address_mode = ZPY, .cycles = 4}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 4}, 
    {.instruction_code = TYA, .address_mode = IMP, .cycles = 2}, {.instruction_code = STA, .address_mode = ABY, .cycles = 5}, {.instruction_code = TXS, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 5}, {.instruction_code = STA, .address_mode = ABX, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = LDY, .address_mode = IMM, .cycles = 2}, {.instruction_code = LDA, .address_mode = IDX, .cycles = 2}, {.instruction_code = LDX, .address_mode = IDX, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = LDY, .address_mode = ZP0, .cycles = 3}, {.instruction_code = LDA, .address_mode = ZP0, .cycles = 3}, {.instruction_code = LDX, .address_mode = ZP0, .cycles = 3}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 3}, 
    {.instruction_code = TAY, .address_mode = IMP, .cycles = 2}, {.instruction_code = LDA, .address_mode = IMM, .cycles = 2}, {.instruction_code = TAX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = LDY, .address_mode = ABS, .cycles = 4}, {.instruction_code = LDA, .address_mode = ABS, .cycles = 4}, {.instruction_code = LDX, .address_mode = ABS, .cycles = 4}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 4}, 
    {.instruction_code = BCS, .address_mode = REL, .cycles = 2}, {.instruction_code = LDA, .address_mode = IDY, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = LDY, .address_mode = ZPX, .cycles = 4}, {.instruction_code = LDA, .address_mode = ZPX, .cycles = 4}, {.instruction_code = LDX, .address_mode = ZPY, .cycles = 4}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = CLV, .address_mode = IMP, .cycles = 2}, {.instruction_code = LDA, .address_mode = ABY, .cycles = 4}, {.instruction_code = TSX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 4}, 
    {.instruction_code = LDY, .address_mode = ABX, .cycles = 4}, {.instruction_code = LDA, .address_mode = ABX, .cycles = 4}, {.instruction_code = LDX, .address_mode = ABY, .cycles = 4}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 4}, 
    {.instruction_code = CPY, .address_mode = IMM, .cycles = 2}, {.instruction_code = CMP, .address_mode = IDX, .cycles = 6}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8},
    {.instruction_code = CPY, .address_mode = ZP0, .cycles = 3}, {.instruction_code = DEC, .address_mode = ZP0, .cycles = 3}, {.instruction_code = DEC, .address_mode = ZP0, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = INY, .address_mode = IMP, .cycles = 2}, {.instruction_code = CMP, .address_mode = IMM, .cycles = 2}, {.instruction_code = DEX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = CPY, .address_mode = ABS, .cycles = 4}, {.instruction_code = CMP, .address_mode = ABS, .cycles = 4}, {.instruction_code = DEC, .address_mode = ABS, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6},  
    {.instruction_code = BNE, .address_mode = REL, .cycles = 2}, {.instruction_code = CMP, .address_mode = IDY, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8},  
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = CMP, .address_mode = ZPX, .cycles = 4}, {.instruction_code = DEC, .address_mode = ZPX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6},  
    {.instruction_code = CLD, .address_mode = IMP, .cycles = 2}, {.instruction_code = CMP, .address_mode = ABY, .cycles = 4}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7},  
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = CMP, .address_mode = ABX, .cycles = 4}, {.instruction_code = DEC, .address_mode = ABX, .cycles = 7}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7},  
    {.instruction_code = CPX, .address_mode = IMM, .cycles = 2}, {.instruction_code = SBC, .address_mode = IDX, .cycles = 6}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8}, 
    {.instruction_code = CPX, .address_mode = ZP0, .cycles = 3}, {.instruction_code = SBC, .address_mode = ZP0, .cycles = 3}, {.instruction_code = INC, .address_mode = ZP0, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 5}, 
    {.instruction_code = INX, .address_mode = IMP, .cycles = 2}, {.instruction_code = SBC, .address_mode = IMM, .cycles = 2}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, 
    {.instruction_code = CPX, .address_mode = ABS, .cycles = 4}, {.instruction_code = SBC, .address_mode = ABS, .cycles = 4}, {.instruction_code = INC, .address_mode = ABS, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = BEQ, .address_mode = REL, .cycles = 2}, {.instruction_code = SBC, .address_mode = IDY, .cycles = 5}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 8},
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = SBC, .address_mode = ZPX, .cycles = 4}, {.instruction_code = INC, .address_mode = ZPX, .cycles = 6}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 6}, 
    {.instruction_code = SED, .address_mode = IMP, .cycles = 2}, {.instruction_code = SBC, .address_mode = ABY, .cycles = 4}, {.instruction_code = NOP, .address_mode = IMP, .cycles = 2}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7}, 
    {.instruction_code = NOP, .address_mode = IMP, .cycles = 4}, {.instruction_code = SBC, .address_mode = ABX, .cycles = 4}, {.instruction_code = INC, .address_mode = ABX, .cycles = 7}, {.instruction_code = XXX, .address_mode = IMP, .cycles = 7},  
};
// --------------------------------



core_cpu_t core_cpu6502_cpu_init(){
    return (core_cpu_t){
        .fetched = 0x00,
        .n_prgbanks_id = 0x00,
        .opcode = 0x00,
        .cycles = 0,
        .addr_abs = 0x0000,
        .addr_rel = 0x00,
        .clock_count = 0,
    };
}

core_cpu_register_t core_cpu6502_register_init(){
    return (core_cpu_register_t){
        .a = 0x00,
        .x = 0x00,
        .y = 0x00,
        .stack_pointer = 0x00,
        .program_counter = 0x0000,
        .status = 0x00,
    };
}

core_main_bus_t core_bus_init(){
    return (core_main_bus_t){
        .address_line = {0},
    };
}


// LOL this struct is to just to flex, might remove this later 
core_ram_t core_ram_init(core_main_bus_t * bus){
    uint8_t * ptr = bus->address_line;
    return (core_ram_t){
        .buffer = ptr,
        .capacity = KB(2),
        .addressable_range = KB(8),
    };
}

core_program_rom_t core_program_rom_init(core_main_bus_t * bus){
    uint8_t * ptr = (uint8_t *)((uintptr_t)bus->address_line + 0x8000);
    return (core_program_rom_t){
        .program_memory = ptr,
        .capacity = KB(16),
    };
}


uint8_t core_cpu6502_read(core_cpu_t* cpu, core_main_bus_t * bus, const uint16_t address){
    printf("CPU is reading from...\n");
    if (address >= 0x8000 && address <= 0xFFFF){
        // cartridge read
        return bus->address_line[address];
    }
    return 0x00;
}


uint8_t core_cpu6502_read_only(core_cpu_t* cpu, const core_main_bus_t * bus, const uint16_t address){
    if (address >= 0x0000 && address <= (KB(8) - 1)){
        return bus->address_line[address & (KB(2) - 1)]; // Mirroring
    } else if (address >= 0x2000 && address <= 0x3FFF){
        return bus->address_line[0x2000 + (address & 0x0007)];
    } else if (address >= 0x8000 && address <= 0xFFFF){
        // cartridge read only
        return bus->address_line[0x8000 + (address & (cpu->n_prgbanks_id > 1? 0x7FFF : 0x3FFF))];
    }
    return 0x00;
}

void core_cpu6502_write(core_cpu_t* cpu, core_main_bus_t * bus, const uint16_t address, const uint8_t data){
    if (address >= 0x0000 && address <= (KB(8) - 1)){
        bus->address_line[address & (KB(2) - 1)] = data;
    } else if (address >= 0x2000 && address <= 0x3FFF){
        bus->address_line[0x2000 + (address & 0x0007)] = data;
    } else if (address >= 0x8000 && address <= 0xFFFF){
        // cartridge write
        bus->address_line[0x8000 + (address & (cpu->n_prgbanks_id > 1? 0x7FFF : 0x3FFF))] = data;
    }
}

void core_cpu6502_reset(core_cpu_t * __restrict cpu, core_cpu_register_t * __restrict cpu_register, core_main_bus_t * bus){
    cpu->addr_abs = 0xFFFC;
    uint16_t low_word = core_cpu6502_read_only(cpu, bus, cpu->addr_abs + 0);
    uint16_t high_word = core_cpu6502_read_only(cpu, bus, cpu->addr_abs + 1);

    cpu_register->program_counter =  low_word | (high_word << 8);

    cpu_register->a = 0x00;
    cpu_register->x = 0x00;
    cpu_register->y = 0x00;
    cpu_register->stack_pointer = 0xFD;
    cpu_register->status = 0x00 | UNUSED_BIT;

    cpu->addr_abs = 0x0000;
    cpu->addr_rel = 0x0000;
    cpu->fetched = 0x00;

    cpu->cycles = 8;
}


void core_cpu6502_irq(core_cpu_t * __restrict cpu, core_cpu_register_t * __restrict cpu_register, core_main_bus_t * bus){
    if (core_cpu6502_getflag(INTERRUPT_BIT, cpu_register) == 0){
        core_cpu6502_write(cpu, bus, 0x0100 + cpu_register->stack_pointer, (cpu_register->program_counter >> 8) & 0x00FF);
		cpu_register->stack_pointer--;
		core_cpu6502_write(cpu, bus, 0x0100 + cpu_register->stack_pointer, cpu_register->program_counter & 0x00FF);
		cpu_register->stack_pointer--;

        core_cpu6502_setflag(BREAK_BIT, cpu_register, false);
        core_cpu6502_setflag(UNUSED_BIT, cpu_register, true);
        core_cpu6502_setflag(INTERRUPT_BIT, cpu_register, true);
        core_cpu6502_write(cpu, bus, 0x0100 + cpu_register->stack_pointer, cpu_register->program_counter & 0x00FF);
		cpu_register->stack_pointer--;

        cpu->addr_abs = 0xFFFC;
        uint16_t low_word = core_cpu6502_read_only(cpu, bus, cpu->addr_abs + 0);
        uint16_t high_word = core_cpu6502_read_only(cpu, bus, cpu->addr_abs + 1);
        cpu_register->program_counter =  low_word | (high_word << 8);

        cpu->cycles = 7;
    }
}

void core_cpu6502_nmi(core_cpu_t * __restrict cpu, core_cpu_register_t * __restrict cpu_register, core_main_bus_t * bus){
    core_cpu6502_write(cpu, bus, 0x0100 + cpu_register->stack_pointer, (cpu_register->program_counter >> 8) & 0x00FF);
    cpu_register->stack_pointer--;
    core_cpu6502_write(cpu, bus, 0x0100 + cpu_register->stack_pointer, cpu_register->program_counter & 0x00FF);
    cpu_register->stack_pointer--;

    core_cpu6502_setflag(BREAK_BIT, cpu_register, false);
    core_cpu6502_setflag(UNUSED_BIT, cpu_register, true);
    core_cpu6502_setflag(INTERRUPT_BIT, cpu_register, true);
    core_cpu6502_write(cpu, bus, 0x0100 + cpu_register->stack_pointer, cpu_register->program_counter & 0x00FF);
    cpu_register->stack_pointer--;

    cpu->addr_abs = 0xFFFC;
    uint16_t low_word = core_cpu6502_read_only(cpu, bus, cpu->addr_abs + 0);
    uint16_t high_word = core_cpu6502_read_only(cpu, bus, cpu->addr_abs + 1);
    cpu_register->program_counter =  low_word | (high_word << 8);

    cpu->cycles = 7;
}


void core_cpu6502_clock(
    core_cpu_t * __restrict cpu
    , core_cpu_register_t * __restrict cpu_register
    , core_main_bus_t * bus
    , const uint16_t offset // this is to help map read to the program rom
){
    // only goes to the next operation if the cycles is 0
    if (cpu->cycles == 0){
        cpu->opcode = core_cpu6502_read_only(cpu, bus, (offset + cpu_register->program_counter));
        core_cpu6502_setflag(UNUSED_BIT, cpu_register, true);
        cpu_register->program_counter++;
        cpu->cycles = core_lookup[cpu->opcode].cycles;

        uint16_t addressmode_cycle = core_cpu6502_perform_fetch(
            cpu
            , cpu_register
            , bus
            , core_lookup[cpu->opcode].address_mode
        );


        uint16_t operation_cycle = core_cpu6502_perform_operation(
            cpu
            , cpu_register
            , bus
            , core_lookup[cpu->opcode].instruction_code
        );

        cpu->cycles += (addressmode_cycle & operation_cycle);
        core_cpu6502_setflag(UNUSED_BIT, cpu_register, true);
    }
    cpu->cycles--;
}


void core_cpu6502_fetch_into_cpu(core_cpu_t * __restrict cpu, core_main_bus_t * __restrict bus){
    if (!(core_lookup[cpu->opcode].address_mode == IMP)){
        uint8_t absolute_address = cpu->addr_abs;
        cpu->fetched = core_cpu6502_read_only(cpu, bus, absolute_address);
    }
}

// I chose to use a switch statement, because it was easier to see how the code flows
uint8_t core_cpu6502_perform_fetch(
    core_cpu_t * __restrict cpu
    , core_cpu_register_t * __restrict cpu_register
    , core_main_bus_t * bus
    , ADDRESS_MODE_T address_mode
){
    // local variables
    uint8_t cycles = 0;
    uint16_t low_word = 0x0000;
    uint16_t high_word = 0x0000;
    uint16_t low_word_ptr = 0x0000;
    uint16_t high_word_ptr = 0x0000;
    uint16_t temp_ = 0x0000;
    uint16_t ptr = 0x0000;

    switch (address_mode){
        case IMP:
            cpu->fetched = cpu_register->a;
            break;
        case IMM:
            cpu->addr_abs = cpu_register->program_counter++;
            break;
        case ZP0:
            cpu->addr_abs = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            cpu->addr_abs &= 0x00FF;
            break;
        case ZPX:
            cpu->addr_abs = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter) + cpu_register->x;
            cpu_register->program_counter++;
            cpu->addr_abs &= 0x00FF;
            break;
        case ZPY:
            cpu->addr_abs = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter) + cpu_register->y;
            cpu_register->program_counter++;
            cpu->addr_abs &= 0x00FF;
            break;
        case REL:
            cpu->addr_abs = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            if (cpu->addr_rel & 0x80) cpu->addr_rel |= 0xFF00; 
            break;
        case ABS:
            low_word = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            high_word = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            cpu->addr_abs = (high_word << 8) | low_word;
            break;
        case ABX:
            low_word = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            high_word = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            cpu->addr_abs = (high_word << 8) | low_word;
            cpu->addr_abs += cpu_register->x;
            if ((cpu->addr_abs & 0xFF00) != (high_word << 8))
                cycles += 1;
            break;
        case ABY:
            low_word = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            high_word = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            cpu->addr_abs = (high_word << 8) | low_word;
            cpu->addr_abs += cpu_register->y;
            if ((cpu->addr_abs & 0xFF00) != (high_word << 8))
                cycles += 1;
            break;
        case IND:
            low_word_ptr = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            high_word_ptr = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            ptr = (high_word_ptr << 8) | low_word_ptr;
            if (low_word_ptr == 0x00FF)
                cpu->addr_abs = (core_cpu6502_read_only(cpu, bus, ptr & 0xFF00) << 8) | core_cpu6502_read_only(cpu, bus, ptr);
            else
                cpu->addr_abs = (core_cpu6502_read_only(cpu, bus, ptr + 1) << 8) | core_cpu6502_read_only(cpu, bus, ptr);
            break;
        case IDX:
            temp_ = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            low_word = core_cpu6502_read_only(
                cpu
                , bus
                , (uint16_t)(temp_ + (uint16_t)cpu_register->x) & 0x00FF);
            high_word = core_cpu6502_read_only(
                cpu
                , bus
                , (uint16_t)(temp_ + (uint16_t)cpu_register->x + 1) & 0x00FF);
            cpu->addr_abs = (high_word << 8) | low_word; 
            break;
        case IDY:
            temp_ = core_cpu6502_read_only(cpu, bus, cpu_register->program_counter);
            cpu_register->program_counter++;
            low_word = core_cpu6502_read_only(
                cpu
                , bus
                , (uint16_t)(temp_ + (uint16_t)cpu_register->y) & 0x00FF);
            high_word = core_cpu6502_read_only(
                cpu
                , bus
                , (uint16_t)(temp_ + (uint16_t)cpu_register->y + 1) & 0x00FF);
            cpu->addr_abs = (high_word << 8) | low_word; 
            if ((cpu->addr_abs & 0xFF00) != (high_word << 0))
                cycles += 1;
            break;
        default:
            assert(0&&"Invalid address mode");
            break;
    }
    return cycles;
}

uint8_t core_cpu6502_perform_operation(
    core_cpu_t * __restrict cpu
    , core_cpu_register_t * __restrict cpu_register
    , core_main_bus_t * bus
    , INSTRUCTION_CODE_T operator
){
    // Some more local variable, the stack is my friend
    uint8_t cycles = 0;
    uint16_t temp_ = 0x0000;
    switch (operator){
        case BRK:
            cpu_register->program_counter++;
            core_cpu6502_setflag(BREAK_BIT, cpu_register, true);
            core_cpu6502_write(
                cpu
                , bus
                , cpu_register->stack_pointer + 0x0100
                , (cpu_register->program_counter >> 8) & 0x00FF
            );
            cpu_register->stack_pointer--;
            core_cpu6502_write(
                cpu
                , bus
                , cpu_register->stack_pointer + 0x0100
                , cpu_register->program_counter & 0x00FF
            );
            cpu_register->stack_pointer--;
            core_cpu6502_setflag(BREAK_BIT, cpu_register, true);
            core_cpu6502_write(
                cpu
                , bus
                , cpu_register->stack_pointer + 0x0100
                , cpu_register->status
            );
            cpu_register->stack_pointer--;
            cpu_register->program_counter = (uint16_t)core_cpu6502_read_only(cpu, bus, 0xFFFE) 
                | ((uint16_t)core_cpu6502_read_only(cpu, bus, 0xFFFF) << 8);
            break;
        case ORA:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            cpu_register->a |= cpu->fetched;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->a == 0x00);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->a == 0x80);
            cycles += 1;
            break;
        case ASL:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = cpu->fetched << 1;
            core_cpu6502_setflag(CARRY_BIT, cpu_register, (temp_ & 0xFF00) > 0);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            if (core_lookup[cpu->opcode].address_mode == IMP)
                cpu_register->a = temp_ & 0x00FF;
            else
                core_cpu6502_write(cpu, bus, cpu->addr_abs, temp_ & 0x00FF);
            break;
        case PHP:
            core_cpu6502_write(cpu, bus, cpu->addr_abs + 0x0100, cpu_register->a | BREAK_BIT | UNUSED_BIT);
            core_cpu6502_setflag(BREAK_BIT, cpu_register, 0);
            core_cpu6502_setflag(UNUSED_BIT, cpu_register, 0);
            break;
        case TAX:
            cpu_register->x = cpu_register->a;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->x == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->x & 0x0080);
            break;
        case BPL:
            if (!core_cpu6502_getflag(NEGATIVE_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0xFF00) != (cpu_register->program_counter & 0xFF00))
			        cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;
            }
            break;
        case CLC:
            core_cpu6502_setflag(CARRY_BIT, cpu_register, false);
            break;
        case JSR:
            cpu_register->program_counter--;
            core_cpu6502_write(cpu, bus, cpu_register->stack_pointer + 0x0100, (cpu_register->program_counter >> 8) & 0x00FF);
            cpu_register->stack_pointer--;
            core_cpu6502_write(cpu, bus, cpu_register->stack_pointer + 0x0100, cpu_register->program_counter & 0x00FF);
            cpu_register->stack_pointer--;
            cpu_register->program_counter = cpu->addr_abs;
            break;
        case RTS:
            cpu_register->stack_pointer++;
            cpu_register->program_counter = (uint16_t)core_cpu6502_read_only(cpu, bus, cpu_register->stack_pointer + 0x0100);
            cpu_register->stack_pointer++;
            cpu_register->program_counter |= (uint16_t)core_cpu6502_read_only(cpu, bus, cpu_register->stack_pointer + 0x0100) << 8;
            cpu_register->program_counter++;
            break;
        case BIT:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = cpu_register->a & cpu->fetched;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, (temp_ & (1 << 7)));
            core_cpu6502_setflag(OVERFLOW_BIT, cpu_register, (temp_ & (1 << 6)));
            break;
        case TAY:
            cpu_register->y = cpu_register->a;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->y == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->y & 0x0080);
            break;
        case ROL:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = ((uint16_t)cpu->fetched << 1) | core_cpu6502_getflag(CARRY_BIT, cpu_register);
            core_cpu6502_setflag(CARRY_BIT, cpu_register, (temp_ & 0x00FF));
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, (temp_ & 0x0080));
            if (core_lookup[cpu->opcode].address_mode == IMP)
                cpu_register->a = temp_ & 0x00FF;
            else 
                core_cpu6502_write(cpu, bus, cpu->addr_abs, temp_ & 0x00FF);
            break;
        case PLP:
            cpu_register->stack_pointer++;
            cpu_register->status = core_cpu6502_read_only(cpu, bus, 0x0100 + cpu_register->stack_pointer);
            break;
        case AND:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            cpu_register->a &= cpu->fetched;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (cpu_register->a & 0x00FF) == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, (cpu_register->a & 0x0080));
            cycles += 1;
            break;
        case BMI:
            if (core_cpu6502_getflag(NEGATIVE_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0xFF00) != (cpu_register->program_counter & 0x00FF))
                    cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;      
            }
            break;
        case SEC:
            core_cpu6502_setflag(CARRY_BIT, cpu_register, true);
            break;
        case RTI:
            cpu_register->stack_pointer++;
            cpu_register->status = core_cpu6502_read_only(cpu, bus, 0x0100 + cpu_register->stack_pointer);
            cpu_register->status &= ~BREAK_BIT;
            cpu_register->status &= ~UNUSED_BIT;
            cpu_register->stack_pointer++;
            cpu_register->program_counter = (uint16_t)core_cpu6502_read_only(cpu, bus, 0x0100 + cpu_register->stack_pointer);
            cpu_register->stack_pointer++;
            cpu_register->program_counter |= (uint16_t)core_cpu6502_read_only(cpu, bus, 0x0100 + cpu_register->stack_pointer) << 8;
            break;
        case EOR:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            cpu_register->a ^= cpu->fetched;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (cpu_register->a & 0x00FF) == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->a & 0x0080);
            break;
        case LSR:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            core_cpu6502_setflag(CARRY_BIT, cpu_register, cpu->fetched & 0x0001);
            temp_ = cpu->fetched >> 1;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            if (core_lookup[cpu->opcode].address_mode == IMP)
                cpu_register->a = temp_ & 0x00FF;
            else
                core_cpu6502_write(cpu, bus, cpu->addr_abs, temp_ & 0x00FF);
            return 0; 
            break;
        case PHA:
            core_cpu6502_write(cpu, bus, cpu_register->stack_pointer + 0x0100, cpu_register->a);
            cpu_register->stack_pointer--;
            break;
        case JMP:
            cpu_register->program_counter = cpu->addr_abs;
            break;
        case BVC:
            if (!core_cpu6502_getflag(OVERFLOW_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0x00FF) != (cpu_register->program_counter & 0xFF00))
                    cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;
            }
            break;
        case CLI:
            core_cpu6502_setflag(INTERRUPT_BIT, cpu_register, false);
            break;
        case BVS:
            if (core_cpu6502_getflag(OVERFLOW_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0x00FF) != (cpu_register->program_counter & 0xFF00))
                    cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;
            }
            break;
        case ADC:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = (uint16_t)cpu_register->a + (uint16_t)cpu->fetched + (uint16_t)core_cpu6502_getflag(CARRY_BIT, cpu_register);
            core_cpu6502_setflag(CARRY_BIT, cpu_register, temp_ > 255);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0);
            core_cpu6502_setflag(
                OVERFLOW_BIT
                , cpu_register
                , ~(((uint16_t)cpu_register->a ^ (uint16_t)cpu->fetched) 
                    & ((uint16_t)cpu_register->a ^ (uint16_t)temp_))
                    & 0x0080
            );
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x80);
            cpu_register->a = temp_ & 0x00FF;
            cycles += 1;
            break;
        case ROR:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = (core_cpu6502_getflag(CARRY_BIT, cpu_register) << 7) | ((uint16_t)cpu->fetched >> 1);
            core_cpu6502_setflag(CARRY_BIT, cpu_register, (temp_ & 0x01));
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, (temp_ & 0x0080));
            if (core_lookup[cpu->opcode].address_mode == IMP)
                cpu_register->a = temp_ & 0x00FF;
            else 
                core_cpu6502_write(cpu, bus, cpu->addr_abs, temp_ & 0x00FF);
            break;
        case SEI:
            core_cpu6502_setflag(INTERRUPT_BIT, cpu_register, true);
            break;
        case STA:
            core_cpu6502_write(cpu, bus, cpu->addr_abs, cpu_register->a);
            break;
        case STY:
            core_cpu6502_write(cpu, bus, cpu->addr_abs, cpu_register->y);
            break;
        case STX:
            core_cpu6502_write(cpu, bus, cpu->addr_abs, cpu_register->x);
            break;
        case DEY:
            cpu_register->y--;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (cpu_register->y & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->y & 0x0080);
            break;
        case TXA:
            cpu_register->a = cpu_register->x;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->a == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->a & 0x0080);
            break;
        case BCC:
            if (!core_cpu6502_getflag(CARRY_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0x00FF) != (cpu_register->program_counter & 0xFF00))
                    cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;
            }
            break;
        case TYA:
            cpu_register->a = cpu_register->y;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->a == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->a & 0x0080);
            break;
        case TXS:
            cpu_register->stack_pointer = cpu_register->x;
            break;
        case LDY:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            cpu_register->y = cpu->fetched;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->y == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->y & 0x0080);
            cycles += 1;
            break;
        case LDA:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            cpu_register->a = cpu->fetched;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->a == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->a & 0x0080);
            cycles += 1;
            break;
        case LDX:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            cpu_register->x = cpu->fetched;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->x == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->x & 0x0080);
            cycles += 1;
            break;
        case BCS:
            if (core_cpu6502_getflag(CARRY_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0x00FF) != (cpu_register->program_counter & 0xFF00))
                    cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;
            }
            break;
        case CLV:
            core_cpu6502_setflag(OVERFLOW_BIT, cpu_register, false);
            break;
        case TSX:
            cpu_register->y = cpu_register->stack_pointer;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, cpu_register->y == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->y & 0x0080);
            break;
        case CPY:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = (uint16_t) cpu_register->y - (uint16_t)cpu->fetched;
            core_cpu6502_setflag(CARRY_BIT, cpu_register, cpu_register->y >= cpu->fetched);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            cycles += 1;
            break;
        case CMP:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = (uint16_t) cpu_register->a - (uint16_t)cpu->fetched;
            core_cpu6502_setflag(CARRY_BIT, cpu_register, cpu_register->a >= cpu->fetched);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            cycles += 1;
            break;
        case DEC:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = cpu->fetched - 1;
            core_cpu6502_write(cpu, bus, cpu->addr_abs, temp_ & 0x00FF);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            break;
        case CLD:
            core_cpu6502_setflag(DECIMAL_BIT, cpu_register, false);
            break;
        case INY:
            cpu_register->y++;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (cpu_register->y & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->y & 0x0080);
            break;
        case DEX:
            cpu_register->x--;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (cpu_register->x & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->x & 0x0080);
            break;
        case BNE:
            if (!core_cpu6502_getflag(NEGATIVE_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0x00FF) != (cpu_register->program_counter & 0xFF00))
                    cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;
            }
            break;
        case CPX:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = (uint16_t) cpu_register->x - (uint16_t)cpu->fetched;
            core_cpu6502_setflag(CARRY_BIT, cpu_register, cpu_register->x >= cpu->fetched);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            cycles += 1;
            break;
        case SBC:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            uint16_t complement = (uint16_t)cpu->fetched ^ 0x00FF;
            temp_ = (uint16_t)cpu_register->a + complement + (uint16_t)core_cpu6502_getflag(CARRY_BIT, cpu_register);
            core_cpu6502_setflag(CARRY_BIT, cpu_register, temp_ & 0xFF00);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0);
            core_cpu6502_setflag(
                OVERFLOW_BIT
                , cpu_register
                , ((uint16_t)cpu_register->a ^ temp_) & (temp_ ^ complement) & 0x0080
            );
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            cpu_register->a = temp_ & 0x00FF;
            cycles += 1;
            break;
        case INC:
            core_cpu6502_fetch_into_cpu(cpu, bus);
            temp_ = cpu->fetched + 1;
            core_cpu6502_write(cpu, bus, cpu->addr_abs, temp_ & 0x00FF);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (temp_ & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, temp_ & 0x0080);
            break;
        case INX:
            cpu_register->x++;
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (cpu_register->x & 0x00FF) == 0x0000);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->x & 0x0080);
            break;
        case NOP:
            switch (cpu->opcode) {
                case 0x1C:
                case 0x3C:
                case 0x5C:
                case 0x7C:
                case 0xDC:
                case 0xFC:
                    return 1;
                    break;
            }
            return 0;
            break;
        case BEQ:
            if (core_cpu6502_getflag(ZERO_BIT, cpu_register)){
                cpu->cycles++;
                cpu->addr_abs = cpu_register->program_counter + cpu->addr_rel;
                if ((cpu->addr_abs & 0x00FF) != (cpu_register->program_counter & 0xFF00))
                    cpu->cycles++;
                cpu_register->program_counter = cpu->addr_abs;
            }
            break;
        case SED:
            core_cpu6502_setflag(DECIMAL_BIT, cpu_register, true);
            break;
        case PLA:
            cpu_register->stack_pointer++;
            cpu_register->a = core_cpu6502_read_only(cpu, bus, 0x0100 + cpu_register->stack_pointer);
            core_cpu6502_setflag(ZERO_BIT, cpu_register, (cpu_register->a & 0x00FF) == 0);
            core_cpu6502_setflag(NEGATIVE_BIT, cpu_register, cpu_register->a & 0x0080);
            break;
        case XXX:
            break;
        default:
            assert(0&&"Unreachable branch!");
            break;
    }
    return cycles;
}


uint8_t core_cpu6502_getflag(FLAGS6502_T flag, const core_cpu_register_t * cpu_register){
    return ((cpu_register->status & flag) > 0)? 1 : 0;
}

void core_cpu6502_setflag(FLAGS6502_T flag, core_cpu_register_t * cpu_register, bool status_){
    if (status_) 
        cpu_register->status |= flag; 
    else 
        cpu_register->status &= ~flag;
    return;
}