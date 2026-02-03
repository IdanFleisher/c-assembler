#ifndef CREATING_PRODUCT_FILES_H
#define CREATING_PRODUCT_FILES_H

#include "convert_to_machine_code.h" 
#include "second_revise.h"
#include "file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * creates the output files (.ob, .ent, .ext) .
 */
void creating_output_files( char *filename, EncodingTable *encoding_head, DataTable *data_head, entry_for_output *entry_head, extern_for_output *extern_head);

/*
* convert a 15-bit binary number to octal and print it as a 5-digit octal number .
*/

void print_15bit_octal(FILE *file, unsigned short num);

#endif 

