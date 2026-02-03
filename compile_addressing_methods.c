#include "compile_addressing_methods.h"





void add_encoding_to_list(EncodingTable **encoding_head, EncodingTable *new_encoding) {
    EncodingTable *current;
    if (*encoding_head == NULL) {
        *encoding_head = new_encoding;
        new_encoding->next = NULL;
    } else {
        current = *encoding_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_encoding;
        new_encoding->next = NULL;
    }
}

/*add to DataTable */
void add_data_to_list(DataTable **data_head, DataTable *new_data) {
    DataTable *current;
    if (*data_head == NULL) { 
        *data_head = new_data;
        new_data->next = NULL;
    } else {
        current = *data_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_data;
        new_data->next = NULL;
    }
}

/*add to entryTable */
void add_internal_label_to_list(InternalLabelTable **entry_head, InternalLabelTable *new_entry) {
    InternalLabelTable *current;
    if (*entry_head == NULL) { 
        *entry_head = new_entry;
        new_entry->next = NULL;
    } else {
        current = *entry_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_entry;
        new_entry->next = NULL;
    }
}

/*add to externalTable */
void add_external_label_to_list(ExternalLabelTable **external_head, ExternalLabelTable *new_external) {
    ExternalLabelTable *current;
    if (*external_head == NULL) { 
        *external_head = new_external;
        new_external->next = NULL;
    } else {
        current = *external_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_external;
        new_external->next = NULL;
    }
}




/*destination operand */
void compile_addressing_method_2_target(EncodingTable **encoding_head, char *operand, int *data_counter) {
    EncodingTable *new_encoding;
    unsigned short machine_code = 0;

    /* allocate memory for new encoding */
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    operand = skip_whitespace(operand);

    /* remove '*' if present */
    if (*operand == '*') {
        operand++;
    }

    /* get rid of trailing whitespace */
    operand = strtok(operand, " \t\n");
    if (operand == NULL) {
        printf("Error: Operand is null after strtok.\n");
        free(new_encoding);
        return;
    }


    /* copy the operand name to the encoding table */
    strncpy(new_encoding->name, operand, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    /* set the decimal address and increment the data counter */
    new_encoding->decimal_address = *data_counter;
    (*data_counter)++;

    /* set bits 0-2 to 'A' */
    machine_code |= (1 << 2);

    /* find which register it is and set bits 3-5  */
    if (strcmp(operand, R0) == 0) {
        machine_code &= ~((1 << 6) | (1 << 7) | (1 << 8));
    }
    else if (strcmp(operand, R1) == 0) {
        machine_code |= (1 << 3); /* R1 */

    } else if (strcmp(operand, R2) == 0) {
        machine_code |= (1 << 4); /* R2 */

    } else if (strcmp(operand, R3) == 0) {
        machine_code |= (1 << 3) | (1 << 4); /* R3 */

    } else if (strcmp(operand, R4) == 0) {
        machine_code |= (1 << 5); /* R4 */

    } else if (strcmp(operand, R5) == 0) {
        machine_code |= (1 << 3) | (1 << 5); /* R5 */

    } else if (strcmp(operand,R6) == 0) {
        machine_code |= (1 << 4) | (1 << 5); /* R6 */

    } else if (strcmp(operand, R7) == 0) {
        machine_code |= (1 << 3) | (1 << 4) | (1 << 5); /* R7 */

    } else {
        printf("Error: Unknown register '%s'\n", operand);
        free(new_encoding);
        return;
    }

    
    new_encoding->machine_code = machine_code;

    

    /* sdd the new encoding to list */
    add_encoding_to_list(encoding_head, new_encoding);
}






/*source operand */
void compile_addressing_method_2_source(EncodingTable **encoding_head, char *operand, int *data_counter) {
    EncodingTable *new_encoding;
    
    unsigned short machine_code = 0;

    
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    operand = skip_whitespace(operand);

    /* remove '*' if present */
    if (*operand == '*') {
        operand++;
    }

    /* trim trailing whitespace */
    operand = strtok(operand, " \t\n");
    if (operand == NULL) {
        printf("Error: Operand is null after strtok.\n");
        free(new_encoding);
        return;
    }


    /* copy the operand name to the encoding table */
    strncpy(new_encoding->name, operand, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    /* set the decimal address and increment the data counter */
    new_encoding->decimal_address = *data_counter;
    (*data_counter)++;

    /* Set bits 0-2 to 'A' */
    machine_code |= (1 << 2);

    /* determine which register it is and set bits 6-8 accordingly */
    if (strcmp(operand, R0) == 0) {
        machine_code &= ~((1 << 6) | (1 << 7) | (1 << 8));
    }
    else if (strcmp(operand, R1) == 0) {
        machine_code |= (1 << 6); /* R1 */
    } else if (strcmp(operand, R2) == 0) {
        machine_code |= (1 << 7); /* R2 */
    } else if (strcmp(operand, R3) == 0) {
        machine_code |= (1 << 6) | (1 << 7); /* R3 */
    } else if (strcmp(operand, R4) == 0) {
        machine_code |= (1 << 8); /* R4 */
    } else if (strcmp(operand, R5) == 0) {
        machine_code |= (1 << 6) | (1 << 8); /* R5 */
    } else if (strcmp(operand,R6) == 0) {
        machine_code |= (1 << 7) | (1 << 8); /* R6 */
    } else if (strcmp(operand, R7) == 0) {
        machine_code |= (1 << 6) | (1 << 7) | (1 << 8); /* R7 */
    } else {
        printf("Error: Unknown register '%s'\n", operand);
        free(new_encoding);
        return;
    }

    /* store the machine code */
    new_encoding->machine_code = machine_code;

    /* add the new encoding to the encoding list */
    add_encoding_to_list(encoding_head, new_encoding);
}





/* share word */
void shared_code_word_method_2(EncodingTable **encoding_head, char *operand_source, char *operand_target, int *data_counter) {
    EncodingTable *new_encoding;
    unsigned short machine_code = 0;


    /* allocate memory for new encoding */
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    operand_source = skip_whitespace(operand_source);
    operand_target = skip_whitespace(operand_target);

    /* remove '*' if present */
    if (*operand_source == '*') {
        operand_source++;
    }
    if (*operand_target == '*') {
        operand_target++;
    }


    /* trim trailing whitespace */
    operand_source = strtok(operand_source, " \t\n");
    if (operand_source == NULL) {
        printf("Error: operand_source is null after strtok.\n");
        free(new_encoding);
        return;
    }
    /* trim trailing whitespace */
    operand_target = strtok(operand_target, " \t\n");
    if (operand_target == NULL) {
        printf("Error: operand_target is null after strtok.\n");
        free(new_encoding);
        return;
    }    

    /* copy the operand name to the encoding table */ 
    strncpy(new_encoding->name, operand_source, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    /* set the decimal address and increment the data counter */
    new_encoding->decimal_address = *data_counter;
    (*data_counter)++;

    /* set bits 0-2 to 'A' */
    machine_code |= (1 << 2);


    /* determine which register it is and set bits 3-5 accordingly */
    if (strcmp(operand_target, R0) == 0) {
        machine_code &= ~((1 << 3) | (1 << 4) | (1 << 5));
    }
    else if (strcmp(operand_target, R1) == 0) {
        machine_code |= (1 << 3); /* R1 */
    } else if (strcmp(operand_target, R2) == 0) {
        machine_code |= (1 << 4); /* R2 */
    } else if (strcmp(operand_target, R3) == 0) {
        machine_code |= (1 << 3) | (1 << 4); /* R3 */
    } else if (strcmp(operand_target, R4) == 0) {
        machine_code |= (1 << 5); /* R4 */
    } else if (strcmp(operand_target, R5) == 0) {
        machine_code |= (1 << 3) | (1 << 5); /* R5 */
    } else if (strcmp(operand_target, R6) == 0) {
        machine_code |= (1 << 4) | (1 << 5); /* R6 */
    } else if (strcmp(operand_target, R7) == 0) {
        machine_code |= (1 << 3) | (1 << 4) | (1 << 5); /* R7 */
    } else {
        printf("Error: Unknown register '%s'\n", operand_target);
        free(new_encoding);
        return;
    }

    /* determine which register it is and set bits 6-8 accordingly */
    if (strcmp(operand_source, R0) == 0) {
        machine_code &= ~((1 << 6) | (1 << 7) | (1 << 8));
    }
    else if (strcmp(operand_source, R1) == 0) {
        machine_code |= (1 << 6); /* R1 */
    } else if (strcmp(operand_source, R2) == 0) {
        machine_code |= (1 << 7); /* R2 */
    } else if (strcmp(operand_source, R3) == 0) {
        machine_code |= (1 << 6) | (1 << 7); /* R3 */
    } else if (strcmp(operand_source, R4) == 0) {
        machine_code |= (1 << 8); /* R4 */
    } else if (strcmp(operand_source, R5) == 0) {
        machine_code |= (1 << 6) | (1 << 8); /* R5 */
    } else if (strcmp(operand_source, R6) == 0) {
        machine_code |= (1 << 7) | (1 << 8); /* R6 */
    } else if (strcmp(operand_source, R7) == 0) {
        machine_code |= (1 << 6) | (1 << 7) | (1 << 8); /* R7 */
    } else {
        printf("Error: Unknown register '%s'\n", operand_source);
        free(new_encoding);
        return;
    }

    /* store the machine code */
    new_encoding->machine_code = machine_code;

     /* add the new encoding to the encoding list */
    add_encoding_to_list(encoding_head, new_encoding);
}








void compile_addressing_method_1(EncodingTable **encoding_head, char *operand, int *data_counter
    , int line_number) {
    EncodingTable *new_encoding;

  
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    operand = skip_whitespace(operand);

    /* trim trailing whitespace */
    operand = strtok(operand, " \t\n");

    
    strncpy(new_encoding->name, operand, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    /* set the decimal address and increment the data counter */
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    (*data_counter)++;

    /* initialize the machine_code to 0 */
    new_encoding->machine_code = 0;


    /* add the new encoding to the encoding list */
    add_encoding_to_list(encoding_head, new_encoding);
}

void compile_addressing_method_0(EncodingTable **encoding_head, char *operand, int *data_counter) {
    EncodingTable *new_encoding;
    int value;
    unsigned short machine_code = 0;

  
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    operand = skip_whitespace(operand);


    
    strncpy(new_encoding->name, operand, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    
    new_encoding->decimal_address = *data_counter;
    (*data_counter)++;

    /* remove '#' if present and convert the remaining string to an integer */
    if (*operand == '#') {
        operand++;
    }
    value = atoi(operand);

    /* handle two's complement for negative numbers */
    machine_code = (unsigned short)(value & 0x7FFF); /* mask to 15 bits */
    if (value < 0) {
        machine_code = (unsigned short)(~(-value) + 1); /* two's complement */
    }

    
    new_encoding->machine_code = machine_code;

    /* add the new encoding to the encoding list */
    add_encoding_to_list(encoding_head, new_encoding);
}

/*destination operand */
void compile_addressing_method_3_target(EncodingTable **encoding_head, char *operand, int *data_counter) {
    EncodingTable *new_encoding;
    unsigned short machine_code = 0;

   
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    operand = skip_whitespace(operand);

    /* trim trailing whitespace */
    operand = strtok(operand, " \t\n");
    if (operand == NULL) {
        printf("Error: Operand is null after strtok.\n");
        free(new_encoding);
        return;
    }

    /* copy the operand name to the encoding table */
    strncpy(new_encoding->name, operand, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

   
    new_encoding->decimal_address = *data_counter;
    (*data_counter)++;

    /* set bits 0-2 to 'A' */
    machine_code |= (1 << 2);

    /* determine which register it is and set bits 3-5 accordingly */
    if (strcmp(operand, R0) == 0) {
        machine_code &= ~((1 << 6) | (1 << 7) | (1 << 8));
    }
    else if (strcmp(operand, R1) == 0) {
        machine_code |= (1 << 3); /* R1 */
    } else if (strcmp(operand, R2) == 0) {
        machine_code |= (1 << 4); /* R2 */
    } else if (strcmp(operand, R3) == 0) {
        machine_code |= (1 << 3) | (1 << 4); /* R3 */
    } else if (strcmp(operand, R4) == 0) {
        machine_code |= (1 << 5); /* R4 */
    } else if (strcmp(operand, R5) == 0) {
        machine_code |= (1 << 3) | (1 << 5); /* R5 */
    } else if (strcmp(operand, R6) == 0) {
        machine_code |= (1 << 4) | (1 << 5); /* R6 */
    } else if (strcmp(operand, R7) == 0) {
        machine_code |= (1 << 3) | (1 << 4) | (1 << 5); /* R7 */
    } else {
        printf("Error: Unknown register '%s'\n", operand);
        free(new_encoding);
        return;
    }

    
    new_encoding->machine_code = machine_code;
    

    
    add_encoding_to_list(encoding_head, new_encoding);
}



/* source operand */
void compile_addressing_method_3_source(EncodingTable **encoding_head, char *operand, int *data_counter) {
    EncodingTable *new_encoding;
    unsigned short machine_code = 0;

   
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

   
    operand = skip_whitespace(operand);

    /* trim trailing whitespace */
    operand = strtok(operand, " \t\n");
    if (operand == NULL) {
        printf("Error: Operand is null after strtok.\n");
        free(new_encoding);
        return;
    }

    
    strncpy(new_encoding->name, operand, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

   
    new_encoding->decimal_address = *data_counter;
    (*data_counter)++;

    /* Set bits 0-2 to 'A' */
    machine_code |= (1 << 2);

    /* determine which register it is and set bits 6-8 accordingly */
    if (strcmp(operand, R0) == 0) {
        machine_code &= ~((1 << 6) | (1 << 7) | (1 << 8));
    }
    else if (strcmp(operand, R1) == 0) {
        machine_code |= (1 << 6); /* R1 */
    } else if (strcmp(operand, R2) == 0) {
        machine_code |= (1 << 7); /* R2 */
    } else if (strcmp(operand, R3) == 0) {
        machine_code |= (1 << 6) | (1 << 7); /* R3 */
    } else if (strcmp(operand, R4) == 0) {
        machine_code |= (1 << 8); /* R4 */
    } else if (strcmp(operand, R5) == 0) {
        machine_code |= (1 << 6) | (1 << 8); /* R5 */
    } else if (strcmp(operand, R6) == 0) {
        machine_code |= (1 << 7) | (1 << 8); /* R6 */
    } else if (strcmp(operand, R7) == 0) {
        machine_code |= (1 << 6) | (1 << 7) | (1 << 8); /* R7 */
    } else {
        printf("Error: Unknown register '%s'\n", operand);
        free(new_encoding);
        return;
    }

   
    new_encoding->machine_code = machine_code;

    
 
    add_encoding_to_list(encoding_head, new_encoding);
}

/* share word  */
void shared_code_word_method_3(EncodingTable **encoding_head, char *operand_source, char *operand_target, int *data_counter) {
    EncodingTable *new_encoding;
    unsigned short machine_code = 0;

    
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    operand_source = skip_whitespace(operand_source);
    operand_target = skip_whitespace(operand_target);

    /* trim trailing whitespace */
    operand_source = strtok(operand_source, " \t\n");
    if (operand_source == NULL) {
        printf("Error: operand_source is null after strtok.\n");
        free(new_encoding);
        return;
    }
    /* trim trailing whitespace */
    operand_target = strtok(operand_target, " \t\n");
    if (operand_target == NULL) {
        printf("Error: operand_target is null after strtok.\n");
        free(new_encoding);
        return;
    }

    
    strncpy(new_encoding->name, operand_source, MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    
    new_encoding->decimal_address = *data_counter;
    (*data_counter)++;

    
    machine_code |= (1 << 2);


    /* determine which register it is and set bits 3-5 accordingly */
    if (strcmp(operand_target, R0) == 0) {
        machine_code &= ~((1 << 3) | (1 << 4) | (1 << 5));
    }
    else if (strcmp(operand_target, R1) == 0) {
        machine_code |= (1 << 3); /* R1 */
    } else if (strcmp(operand_target, R2) == 0) {
        machine_code |= (1 << 4); /* R2 */
    } else if (strcmp(operand_target, R3) == 0) {
        machine_code |= (1 << 3) | (1 << 4); /* R3 */
    } else if (strcmp(operand_target, R4) == 0) {
        machine_code |= (1 << 5); /* R4 */
    } else if (strcmp(operand_target, R5) == 0) {
        machine_code |= (1 << 3) | (1 << 5); /* R5 */
    } else if (strcmp(operand_target, R6) == 0) {
        machine_code |= (1 << 4) | (1 << 5); /* R6 */
    } else if (strcmp(operand_target, R7) == 0) {
        machine_code |= (1 << 3) | (1 << 4) | (1 << 5); /* R7 */
    } else {
        printf("Error: Unknown register '%s'\n", operand_target);
        free(new_encoding);
        return;
    }

    /* determine which register it is and set bits 6-8 accordingly */
    if (strcmp(operand_source, R0) == 0) {
        machine_code &= ~((1 << 6) | (1 << 7) | (1 << 8));
    }
    else if (strcmp(operand_source, R1) == 0) {
        machine_code |= (1 << 6); /* R1 */
    } else if (strcmp(operand_source, R2) == 0) {
        machine_code |= (1 << 7); /* R2 */
    } else if (strcmp(operand_source, R3) == 0) {
        machine_code |= (1 << 6) | (1 << 7); /* R3 */
    } else if (strcmp(operand_source, R4) == 0) {
        machine_code |= (1 << 8); /* R4 */
    } else if (strcmp(operand_source, R5) == 0) {
        machine_code |= (1 << 6) | (1 << 8); /* R5 */
    } else if (strcmp(operand_source, R6) == 0) {
        machine_code |= (1 << 7) | (1 << 8); /* R6 */
    } else if (strcmp(operand_source, R7) == 0) {
        machine_code |= (1 << 6) | (1 << 7) | (1 << 8); /* R7 */
    } else {
        printf("Error: Unknown register '%s'\n", operand_source);
        free(new_encoding);
        return;
    }

   
    new_encoding->machine_code = machine_code;

    
    add_encoding_to_list(encoding_head, new_encoding);
}

