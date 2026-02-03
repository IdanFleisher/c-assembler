#ifndef CHECK_ADDRESSING_METHODS_H
#define CHECK_ADDRESSING_METHODS_H

#include "multiple_use.h"

/* 
 * checks if the operand uses immediate addressing mode ( starts with '#').
 * validates that the operand starts with '#' and there is no whitespace between '#' and the number.
 *
 * returns:
 * - 0 if valid immediate addressing is detected.
 * - 1 if the operand is not in immediate addressing mode.
 */
int Instant_addressing(char *operand);

/* 
 * checks if the operand uses indirect register addressing mode (starts with '*').
 * validates that the operand starts with '*' and is followed by a valid register name.
 *
 * returns:
 * - 0 if valid indirect register addressing is detected.
 * - 1 if the operand is not in indirect register addressing mode.
 */
int Indirect_register_addressing(char *operand);

/* 
 * checks if the operand uses direct register addressing mode .
 * validates that the operand is a valid register name and there are no extra characters after it.
 *
 * returns:
 * - 0 if valid direct register addressing is detected.
 * - 1 if the operand is not in direct register addressing mode.
 */
int Direct_register_addressing(char *operand);

#endif 

