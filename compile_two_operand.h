#ifndef COMPILE_TWO_OPERAND_H
#define COMPILE_TWO_OPERAND_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "multiple_use.h"
#include "compile_addressing_methods.h"
#include "check_addressing_methods.h"
#include "convert_to_machine_code.h"
#include "file_reader.h"

/*
 * compiles the 'mov' instruction into machine code and adds it to the encoding list.
 */
void compile_mov_instruction(EncodingTable **encoding_head, int *data_counter, char *operands , int line_number);

/*
 * compiles the 'cmp' instruction into machine code and adds it to the encoding list.
 */
void compile_cmp_instruction(EncodingTable **encoding_head, int *data_counter, char *operands , int line_number);

/*
 * compiles the 'add' instruction into machine code and adds it to the encoding list.
 */
void compile_add_instruction(EncodingTable **encoding_head, int *data_counter, char *operands , int line_number);

/*
 * compiles the 'sub' instruction into machine code and adds it to the encoding list.
 */
void compile_sub_instruction(EncodingTable **encoding_head, int *data_counter, char *operands , int line_number);

/*
 * compiles the 'lea' instruction into machine code and adds it to the encoding list.
 */
void compile_lea_instruction(EncodingTable **encoding_head, int *data_counter, char *operands , int line_number);

/*
 * compiles the '.string' directive and adds the corresponding data to the data list.
 */
void compile_string_instruction(DataTable **data_head, int *data_counter, char *line );

/*
 * compiles the '.data' directive and adds the corresponding data to the data list.
 */
void compile_data_instruction(DataTable **data_head, int *data_counter, char *line );

/*
 * compiles the '.entry' directive and adds the corresponding label to the internal label list.
 */
void compile_entry_instruction(InternalLabelTable **label_head, int *data_counter, char *line);

/*
 * compiles the '.extern' directive and adds the corresponding label to the external label list.
 */
void compile_extern_instruction(ExternalLabelTable **label_head, int *data_counter, char *line);


#endif 

