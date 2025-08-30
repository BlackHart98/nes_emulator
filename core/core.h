#define KB(size_) (size_ * 1024) 

#define LOOKUP_TABLE_SIZE  (16 * 16)

#ifndef _CORE_H
#define _CORE_H

#include <stdint.h>
#include <stdbool.h>
#include "../utils/utils.h"


//@ Module: cpu6502 layout

typedef enum _INSTRUCTION_CODE{
    BRK, ORA, ASL, PHP, TAX, BPL, CLC, JSR, 
    RTS, BIT, TAY, ROL, PLP, AND, BMI, SEC,
    RTI, EOR, LSR, PHA, JMP, BVC, CLI, BVS,
    ADC, ROR, SEI, STA, STY, STX, DEY, TXA,
    BCC, TYA, TXS, LDY, LDA, LDX, BCS, CLV,
    TSX, CPY, CMP, DEC, CLD, INY, DEX, BNE, 
    CPX, SBC, INC, INX, NOP, BEQ, SED, PLA,

    // unofficial opcode
    XXX
} INSTRUCTION_CODE_T;


typedef enum _ADDRESS_MODE{
    IMP, IMM,
    ZP0, ZPX,
    ZPY, REL,
    ABS, ABX,
    ABY, IND,
    IDX, IDY,
} ADDRESS_MODE_T;


// CPU flags
typedef enum _FLAGS6502{
    CARRY_BIT               = (1 << 0),
    ZERO_BIT                = (1 << 1),
    INTERRUPT_BIT           = (1 << 2),
    DECIMAL_BIT             = (1 << 3),
    BREAK_BIT               = (1 << 4),
    UNUSED_BIT              = (1 << 5),
    OVERFLOW_BIT            = (1 << 6),
    NEGATIVE_BIT            = (1 << 7),
} FLAGS6502_T;

typedef struct _core_instruction_t {
    uint8_t             cycles;
    INSTRUCTION_CODE_T  instruction_code;
    ADDRESS_MODE_T      address_mode;
} core_instruction_t;



typedef struct _core_cpu_t{
    uint8_t     fetched;
    uint8_t     opcode;
    uint8_t     cycles;
    uint16_t    addr_abs;
    uint16_t    addr_rel;
    uint32_t    clock_count;
} core_cpu_t;


// CPU Registers
typedef struct _core_cpu_register_t{
    uint8_t a;              // Accumulator register
    uint8_t x;              // X register
    uint8_t y;              // Y register
    uint8_t stack_pointer;
    uint8_t program_counter;
    uint8_t status;         // Flags
} core_cpu_register_t;


//@ Module: bus layout
typedef struct _core_main_bus_t{
    // Address line
    uint8_t address_line[KB(64)];
} core_main_bus_t;

typedef struct _core_ppu_bus_t{
    // Address line
    uint8_t address_line[KB(64)];
} core_ppu_bus_t;


// NES: RAM
typedef struct _core_ram_t{
    uint16_t addressable_range;
    // RAM capacity
    uint16_t capacity;

    // Addressable range on the RAM
    uint8_t* buffer;
} core_ram_t;


// NES: PPU
typedef struct _core_ppu_t{
    uint8_t     cycles;
    uint32_t    clock_count;
} core_ppu_t;



// NES: PPU register
typedef struct _core_ppu_register_t{
    // PPU register count
    uint16_t capacity;
    
    // PPU register content
    uint8_t* ppu_register;
} core_ppu_register_t;


// NES: Cartridge
typedef struct _core_cartridge_t{
    utils_dyn_array_t program_memory;
    utils_dyn_array_t character_memory;
} core_cartridge_t;

// NES: Name table
typedef struct _core_name_table_t {
    uint8_t *   name_table;
    uint16_t    capacity;
} core_name_table_t;


// NES: Pattern
typedef struct _core_pattern_t {
    uint8_t *   pattern_buffer;
    uint16_t    capacity;
} core_pattern_t;


// NES: Palettes
typedef struct _core_palettes_t {
    uint8_t *   palettes_buffer;
    uint16_t    capacity;
} core_palettes_t;


// NES: Program ROM
typedef struct _core_program_rom_t{
    uint8_t *   program_memory;
    uint16_t    capacity;
} core_program_rom_t;



// iNES: Header



// Initialize the cpu struct
extern core_cpu_t core_cpu6502_cpu_init();

// Initialize the cpu register struct
extern core_cpu_register_t core_cpu6502_register_init();

// Initialize the bus struct
extern core_main_bus_t core_bus_init();

// Initialize the ram struct
extern core_ram_t core_ram_init(core_main_bus_t *);

// Initialize the ppu register struct
extern core_ppu_register_t core_ppu2C02_register_init(core_main_bus_t *);

// Initialize the ppu bus struct
extern core_ppu_bus_t core_ppu_bus_init();

// Initialize the cartridge struct
extern core_cartridge_t core_cartridge_init(char *);

// Initialize the name table struct
extern core_name_table_t core_name_table_init(core_ppu_bus_t *);

// Initialize the name table struct
extern core_pattern_t core_pattern_init(core_ppu_bus_t *);

// Initialize the name table struct
extern core_ppu_t core_ppu2C02_init();


// Initialize the name table struct
extern core_ppu_t core_ppu2C02_init();


// Deinitialize the cartridge struct
extern void core_cartridge_deinit(core_cartridge_t *);


// CPU functions
extern uint8_t core_cpu6502_read(core_main_bus_t *, const uint16_t);
extern uint8_t core_cpu6502_read_only(const core_main_bus_t *, const uint16_t);
extern void core_cpu6502_write(core_main_bus_t *, const uint16_t, const uint8_t);
extern void core_cpu6502_reset(core_cpu_t * __restrict, core_cpu_register_t * __restrict, core_main_bus_t *);
extern void core_cpu6502_irq(core_cpu_t * __restrict, core_cpu_register_t * __restrict, core_main_bus_t *);
extern void core_cpu6502_nmi(core_cpu_t * __restrict, core_cpu_register_t * __restrict, core_main_bus_t *);
extern void core_cpu6502_clock(core_cpu_t * __restrict, core_cpu_register_t * __restrict, core_main_bus_t *);

extern void core_cpu6502_fetch_into_cpu(core_cpu_t * __restrict, core_main_bus_t * __restrict);
extern uint8_t core_cpu6502_perform_fetch(core_cpu_t * __restrict, core_cpu_register_t * __restrict, core_main_bus_t *, ADDRESS_MODE_T);
extern uint8_t core_cpu6502_perform_operation(core_cpu_t * __restrict, core_cpu_register_t * __restrict, core_main_bus_t *, INSTRUCTION_CODE_T);

extern uint8_t core_cpu6502_getflag(FLAGS6502_T, const core_cpu_register_t *);
extern void core_cpu6502_setflag(FLAGS6502_T, core_cpu_register_t *, bool);


// PPU functions
extern uint8_t core_ppu2C02_read_from_main_bus(core_ppu_register_t *, const uint16_t);
extern void core_ppu2C02_write_to_main_bus(core_ppu_register_t *, const uint16_t, const uint8_t);
extern uint8_t core_ppu2C02_read_from_ppu_bus(core_ppu_bus_t *, const uint16_t);
extern void core_ppu2C02_write_to_ppu_bus(core_ppu_bus_t *, const uint16_t, const uint8_t);
extern void core_ppu2C02_clock(core_ppu_t *);


// Mapper functions
extern void core_map_cartridge_to_addressable_prgrom(core_cartridge_t *, core_program_rom_t *);
extern void core_map_cartridge_to_addressable_chrrom(core_cartridge_t *, core_palettes_t *);


// Cartridge functions
extern uint8_t core_prgrom_read_from_main_bus(core_program_rom_t *, const uint16_t);
extern void core_prgrom_write_to_main_bus(core_program_rom_t *, const uint16_t, const uint8_t);
extern uint8_t core_pattern_read_from_ppu_bus(core_pattern_t *, const uint16_t);
extern void core_pattern_write_to_ppu_bus(core_pattern_t *, const uint16_t, const uint8_t);



// NES Emulator
extern int core_nes_emulate(
    core_main_bus_t *           main_bus
    , core_cpu_t *              cpu
    , core_cpu_register_t *     cpu_register
    , core_ram_t *              cpu_ram
    , core_ppu_bus_t *          ppu_bus
    , core_ppu_register_t *     ppu
    , core_cartridge_t *        cartridge
);

#endif