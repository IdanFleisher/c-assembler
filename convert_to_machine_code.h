#ifndef CONVERT_TO_MACHINE_CODE_H
#define CONVERT_TO_MACHINE_CODE_H

#include "multiple_use.h"
#include "file_reader.h"
#include "validate_code.h"


#define MACHINE_CODE_LENGTH 15 

typedef struct LabelTable{ /*lable list */
    char label_name[MAX_MACRO_NAME_LENGTH ];
    int decimal_address;
    struct LabelTable *next;  
} LabelTable;

typedef struct EncodingTable{ /*  encoding table */
    char name[MAX_MACRO_NAME_LENGTH ];
    int decimal_address;
    int number_line_s;  /* line number of struct updating in am_check */
    unsigned short machine_code; 
    struct EncodingTable *next;  
} EncodingTable;

typedef struct DataTable{ /*  data table */
    char name[MAX_MACRO_NAME_LENGTH ];
    int decimal_address;
    unsigned short machine_code; 
    struct DataTable *next;  
} DataTable;

typedef struct ExternalLabelTable{ /*  external lable table */
    char name[MAX_MACRO_NAME_LENGTH ];
    int decimal_address;
    struct ExternalLabelTable *next;  
} ExternalLabelTable;

typedef struct InternalLabelTable{  /*  internal lable table */
    char name[MAX_MACRO_NAME_LENGTH ];
    int decimal_address;
    struct InternalLabelTable *next;  
} InternalLabelTable;

/* 
 * converts a line of assembly code into machine code and stors it in the correct table.
 * this function handles labels, instructions, and directives, converting them into their machine code.
 * it updates the label, encoding, data, external, and internal label tables when needed.
 *
 *
 * - exists_error: if non zero, compilation is stopped because of an error in the source code.
 * - has_label: indicates if the current line contains a label to be processed.
 * - data_counter: pointer to the counter tracking the current memory location.
 * - line_number: the line number of the current line in the source file.
 * - line: the current line of assembly code being processed.
 * - label_head: pointer to the head of the label table .
 * - encoding_head: pointer to the head of the encoding table .
 * - data_head: pointer to the head of the data table.
 * - external_head: pointer to the head of the external label table.
 * - internal_head: pointer to the head of the internal label table.
 */
void convert_to_machine_code(int exists_error, int has_label, int *data_counter , int line_number, char *line , LabelTable **label_head
,EncodingTable **encoding_head , DataTable **data_head ,ExternalLabelTable **external_head ,InternalLabelTable **internal_head);

#endif 

