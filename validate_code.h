#ifndef VALIDATE_CODE_H
#define VALIDATE_CODE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "multiple_use.h"
#include "check_addressing_methods.h"

/* 
 * checks if a line starts with 'stop' or 'rts', which are non-operand instructions.
 * validates that these instructions are not followed by extra characters.
 *
 * returns:
 * - 0 if valid (no extra characters after 'stop' or 'rts').
 * - 1 if there are extra characters after the instruction.
 */
int check_non_operand_instructions(char *line, int line_number);

/* 
 * checks if a line contains a valid one-operand instruction (like 'clr', 'jmp', etc.).
 * validates that the instruction is followed by exactly one operand and nothing else.
 *
 * returns:
 * - 0 if valid (one operand is present).
 * - 1 if there are no operands or extra operands after the instruction.
 */
int check_one_operand_instructions(char *line, int line_number);

/* 
 * checks if a line contains a valid two-operand instruction (like 'mov', 'cmp', etc.).
 * ensures the instruction is followed by exactly two operands, separated by a comma.
 *
 * returns:
 * - 0 if valid (two operands are present).
 * - 1 if there are missing or extra operands or if a comma is missing.
 */
int check_two_operand_instructions(char *line, int line_number);

/* 
 * checks if a line contains a valid '.data' directive followed by a list of integers.
 * ensures the integers are correctly separated by commas.
 *
 * returns:
 * - 0 if valid (properly formatted list of integers).
 * - 1 if there are syntax errors, missing numbers, or trailing commas.
 */
int check_data_directive(char *line, int line_number);

/* 
 * checks if a line contains a valid '.string' directive followed by a quoted string.
 * ensures that the string is correctly enclosed in quotes.
 *
 * returns:
 * - 0 if valid (properly formatted string in quotes).
 * - 1 if there are syntax errors, missing quotes, or invalid characters.
 */
int check_string_directive(char *line, int line_number);

/* 
 * checks if a line starts with the '.entry' or '.extern' directive followed by a valid label.
 * validates that the directive is followed by a single label and nothing else.
 *
 * returns:
 * - 0 if valid (correct directive followed by a single label).
 * - 1 if there are syntax errors or extra characters after the label.
 */
int check_entry_and_extern_directive(char *line, int line_number);

#endif 

