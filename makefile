assembler: file_reader.o macro_handler.o am_check.o multiple_use.o validate_code.o convert_to_machine_code.o check_addressing_methods.o compile.o compile_addressing_methods.o compile_two_operand.o second_revise.o creating_product_files.o  assembler.o
	gcc -g -ansi -Wall -pedantic file_reader.o macro_handler.o am_check.o multiple_use.o validate_code.o convert_to_machine_code.o check_addressing_methods.o compile.o compile_addressing_methods.o compile_two_operand.o second_revise.o creating_product_files.o assembler.o -o assembler

file_reader.o: file_reader.c file_reader.h multiple_use.h macro_handler.h
	gcc -c -ansi -Wall -pedantic file_reader.c -o file_reader.o 

macro_handler.o: macro_handler.c macro_handler.h file_reader.h multiple_use.h
	gcc -c -ansi -Wall -pedantic macro_handler.c -o macro_handler.o 

am_check.o: am_check.c am_check.h file_reader.h multiple_use.h macro_handler.h validate_code.h convert_to_machine_code.h second_revise.h
	gcc -c -ansi -Wall -pedantic am_check.c -o am_check.o 

multiple_use.o: multiple_use.c multiple_use.h
	gcc -c -ansi -Wall -pedantic multiple_use.c -o multiple_use.o 

validate_code.o: validate_code.c validate_code.h multiple_use.h
	gcc -c -ansi -Wall -pedantic validate_code.c -o validate_code.o 

convert_to_machine_code.o: convert_to_machine_code.c convert_to_machine_code.h compile.h compile_two_operand.h
	gcc -c -ansi -Wall -pedantic convert_to_machine_code.c -o convert_to_machine_code.o 

check_addressing_methods.o: check_addressing_methods.c check_addressing_methods.h multiple_use.h
	gcc -c -ansi -Wall -pedantic check_addressing_methods.c -o check_addressing_methods.o 

compile.o: compile.c compile.h multiple_use.h convert_to_machine_code.h compile_addressing_methods.h check_addressing_methods.h
	gcc -c -ansi -Wall -pedantic compile.c -o compile.o 

compile_addressing_methods.o: compile_addressing_methods.c compile_addressing_methods.h multiple_use.h convert_to_machine_code.h
	gcc -c -ansi -Wall -pedantic compile_addressing_methods.c -o compile_addressing_methods.o 

compile_two_operand.o: compile_two_operand.c compile_two_operand.h multiple_use.h compile_addressing_methods.h check_addressing_methods.h convert_to_machine_code.h file_reader.h
	gcc -c -ansi -Wall -pedantic compile_two_operand.c -o compile_two_operand.o 

second_revise.o: second_revise.c second_revise.h creating_product_files.h convert_to_machine_code.h am_check.h file_reader.h
	gcc -c -ansi -Wall -pedantic second_revise.c -o second_revise.o 

creating_product_files.o: creating_product_files.c creating_product_files.h convert_to_machine_code.h second_revise.h file_reader.h
	gcc -c -ansi -Wall -pedantic creating_product_files.c -o creating_product_files.o 

assembler.o: assembler.c file_reader.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o 
