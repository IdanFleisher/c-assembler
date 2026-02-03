# Two-Pass Assembler (ANSI C)

A modular two-pass assembler written in ANSI C that translates assembly source files into binary machine code.

This project implements a full compilation pipeline including macro expansion, syntax validation, symbol resolution, and instruction encoding.

Designed as part of a low-level systems programming course with emphasis on clean architecture, separation of concerns, and maintainable C code.

---

## Features

- Two-pass assembly process (first pass + second pass)
- Macro preprocessing
- Symbol table management
- Multiple addressing methods
- Instruction validation
- Binary machine code generation
- Creation of output product files
- Robust error detection and reporting

---

## Architecture

The project is organized into independent modules:

### Core compilation
- `compile.c` – main compilation flow
- `second_revise.c` – second pass symbol resolution
- `convert_to_machine_code.c` – instruction encoding

### Parsing & validation
- `validate_code.c` – syntax and semantic checks
- `check_addressing_methods.h` – addressing validation

### Addressing methods
- `compile_addressing_methods.c`
- `compile_two_operand.c`

### Preprocessing
- `macro_handler.c` – macro expansion

### File handling
- `file_reader.c` – input parsing
- `creating_product_files.c` – output file generation

### Utilities
- `multiple_use.c` – shared helper functions

---

## Technologies

- ANSI C
- Linux / Ubuntu
- GCC
- Makefile build system

---

## Build & Run

```bash
make
./assembler <input_file>
