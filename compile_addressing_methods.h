#ifndef COMPILE_ADDRESSING_METHODS_H
#define COMPILE_ADDRESSING_METHODS_H

#include <stdio.h>
#include <string.h>
#include "multiple_use.h"
#include "convert_to_machine_code.h"

/* 
 * adds a new encoding to the encoding list.
 * the new encoding is joined to the end of the linked list.
 */
void add_encoding_to_list(EncodingTable **encoding_head, EncodingTable *new_encoding);

/* 
 * adds a new data entry to the data table.
 * the new data entry is joined to the end of the linked list.
 */
void add_data_to_list(DataTable **encoding_head, DataTable *new_encoding);

/* 
 * adds a new entry to the internal label table.
 * the new entry is joined to the end of the linked list.
 */
void add_internal_label_to_list(InternalLabelTable **entry_head, InternalLabelTable *new_entry);

/* 
 * adds a new entry to the external label table.
 * the new entry is joined to the end of the linked list.
 */
void add_external_label_to_list(ExternalLabelTable **external_head, ExternalLabelTable *new_external);

/* 
 * compiles an operand using addressing method 2 for the destination operand.
 * the operand is processed and its machine code is added to the encoding table.
 */
void compile_addressing_method_2_target(EncodingTable **encoding_head, char *operand, int *data_counter);

/* 
 * compiles an operand using addressing method 2 for the source operand.
 * the operand is processed and its machine code is added to the encoding table.
 */
void compile_addressing_method_2_source(EncodingTable **encoding_head, char *operand, int *data_counter);

/* 
 * compiles a shared code word for addressing method 2 using both source and target operands.
 * the source and target operands are combined into a single machine code word.
 */
void shared_code_word_method_2(EncodingTable **encoding_head, char *operand_source, char *operand_target, int *data_counter);

/* 
 * compiles an operand using addressing method 1.
 * the operand is processed and its machine code is added to the encoding table.
 */
void compile_addressing_method_1(EncodingTable **encoding_head, char *operand, int *data_counter , int line_number);

/* 
 * compiles an operand using addressing method 0 .
 * the operand is processed and its machine code is added to the encoding table.
 */
void compile_addressing_method_0(EncodingTable **encoding_head, char *operand, int *data_counter);

/* 
 * compiles an operand using addressing method 3 for the destination operand.
 * the operand is processed and its machine code is added to the encoding table.
 */
void compile_addressing_method_3_target(EncodingTable **encoding_head, char *operand, int *data_counter);

/* 
 * compiles an operand using addressing method 3 for the source operand.
 * the operand is processed and its machine code is added to the encoding table.
 */
void compile_addressing_method_3_source(EncodingTable **encoding_head, char *operand, int *data_counter);

/* 
 * compiles a shared code word for addressing method 3 using both source and target operands.
 * the source and target operands are combined into a single machine code word.
 */
void shared_code_word_method_3(EncodingTable **encoding_head, char *operand_source, char *operand_target, int *data_counter);

#endif 

