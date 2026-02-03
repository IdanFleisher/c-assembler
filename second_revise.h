#ifndef SECOND_REVISE_H
#define SECOND_REVISE_H

#include "convert_to_machine_code.h" 
#include "am_check.h"
#include "file_reader.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/*
 * struct to store entry labels for output
 */
typedef struct entry_for_output {
    char name[MAX_MACRO_NAME_LENGTH +1]; 
    int position;  /* the position in regard to decimal_address */
    struct entry_for_output *next;
} entry_for_output;

/*
 * struct to store extern labels for output
 */
typedef struct extern_for_output {
    char name[MAX_MACRO_NAME_LENGTH +1]; 
    int position;  /* the position in regard to decimal_address */
    struct extern_for_output *next;
} extern_for_output;

/*
 * reprocesses the file and handles entry and extern directives, generates output files
 */
void reprocess_file( char *filename, int error_flag, LabelTable *label_table, EncodingTable *encoding_table, 
                  DataTable *data_table, ExternalLabelTable *external_label_table, InternalLabelTable *internal_label_table);

/*
 * checks for errors related to .entry directive
 */
int check_entry_directive( char *line, LabelTable *label_table, int line_number ,entry_for_output **entry_head );

/*
 * checks for errors related to .extern directive
 */
int check_extern_directive( char *line, LabelTable *label_table, int line_number);

/*
 * compares labels in encoding table with the label and external tables
 */
void compare_label(EncodingTable *encoding_head, LabelTable *label_head, ExternalLabelTable *external_label_head, int *error_flag , extern_for_output **extern_head);

#endif 

