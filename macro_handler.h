#ifndef MACRO_HANDLER_H
#define MACRO_HANDLER_H

#include "file_reader.h"
#include "multiple_use.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Handles the start of a macro definition, verifying format and storing it.
 * This function checks if the macro declaration is correct, ensuring it follows the format 'macr macro_name',
 * and adds it to the macro list if valid.
 */
void handleMacroStart(char *line, Macro **macros, int *macro_count, int *macro_capacity, int *macro_flag, Macro **current_macro, int *has_error, char *filename, int line_number);

/* 
 * Handles the end of a macro definition, verifying correct end format.
 * This function ensures that the macro end statement follows the format 'endmacr' with no additional tokens.
 */
void handleMacroEnd(char *line, int *macro_flag, int *has_error, char *filename, int line_number);

/* 
 * Adds a line to the current macro, expanding storage if necessary.
 * This function appends a line to the currently open macro, reallocating memory for lines if needed.
 */
void handleMacroLine(char *line, Macro *current_macro);

/* 
 * Handles lines of assembly code, expanding macros where used.
 * This function processes non-macro lines, expanding any macros used within them by replacing the macro name
 * with its expanded definition.
 */
void handleRegularLine(char *line, FILE *output, Macro **macros, int macro_count, char *filename, int line_number);

/* 
 * Validates macro names to ensure they start with a letter and are of valid length.
 * This function checks the macro name against criteria, such as starting with an alphabetic character and not
 * exceeding the maximum length.
 *
 * Returns:
 * - 1 if the name is valid, 0 otherwise.
 */
int isValidMacroName(char *name);

/* 
 * Checks if a given name is reserved and cannot be used as a macro name.
 * This function verifies if the macro name matches any reserved words that are not allowed as macro names.
 *
 * Returns:
 * - 1 if the name is reserved, 0 otherwise.
 */
int isReservedWord(char *name);

/* 
 * Checks for duplicate macro names to prevent redefinition.
 * This function ensures that a macro name has not been previously defined to avoid conflicts.
 *
 * Returns:
 * - 1 if the macro name is a duplicate, 0 otherwise.
 */
int isMacroNameDuplicate(Macro **macros, int macro_count, char *name);

/* 
 * Verifies that a line containing "macr" is formatted correctly.
 * This function checks if "macr" is the first non-whitespace text on a line, ensuring proper formatting.
 *
 * Returns:
 * - 1 if the line is correctly formatted, 0 otherwise.
 */
int isMacrLineFormattedCorrectly(char *line);

/* Check if a macro name is used alone on a line */
int isMacroNameAloneOnLine(char *line, char *macro_name);

/* Check if a macro name is incorrectly used as a label */
int isMacroNameUsedAsLabel(char *line, char *macro_name);

#endif 
