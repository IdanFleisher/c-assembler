#ifndef COMPILE_H
#define COMPILE_H

#include <stdio.h>
#include <stdlib.h>
#include "multiple_use.h"
#include "convert_to_machine_code.h"
#include "compile_addressing_methods.h"
#include "check_addressing_methods.h"



/*
 * compiles s the 'stop' instruction into machine code and adds it to the encoding list.
 */
void compile_stop_instruction(EncodingTable **encoding_head, int *data_counter , int line_number);

/*
 * compiles  the 'rts' instruction into machine code and adds it to the encoding list.
 */
void compile_rts_instruction(EncodingTable **encoding_head, int *data_counter , int line_number);

/*
 * compiles  the 'jsr' instruction into machine code and adds it to the encoding list.
 */
void compile_jsr_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 * compiles  the 'bne' instruction into machine code and adds it to the encoding list.
 */
void compile_bne_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 * compiles the 'jmp' instruction into machine code and adds it to the encoding list.
 */
void compile_jmp_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 *compiles the 'red' instruction into machine code and adds it to the encoding list.
 */
void compile_red_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 *compiles the 'dec' instruction into machine code and adds it to the encoding list.
 */
void compile_dec_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 * compiles the 'inc' instruction into machine code and adds it to the encoding list.
 */
void compile_inc_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 * compiles  the 'not' instruction into machine code and adds it to the encoding list.
 */
void compile_not_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 * compiles the 'clr' instruction into machine code and adds it to the encoding list.
 */
void compile_clr_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

/*
 * compiles the 'prn' instruction into machine code and adds it to the encoding list.
 */
void compile_prn_instruction(EncodingTable **encoding_head, int *data_counter, char *operand, int line_number);

#endif 

