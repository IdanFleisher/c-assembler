#include "second_revise.h"
#include "creating_product_files.h"


void reprocess_file( char *filename, int error_flag, LabelTable *label_table, EncodingTable *encoding_table, 
                  DataTable *data_table, ExternalLabelTable *external_label_table, InternalLabelTable *internal_label_table) {
    FILE *file;
    char *line;
    int line_number = 0;
    char *trimmed_line;
    char *label_end;
        
    entry_for_output *entry_head = NULL;
    entry_for_output *current_entry;

    extern_for_output *extern_head = NULL;
    extern_for_output *current_extern;

    /* open the file again for reprocessing */
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s for reprocessing\n", filename);
        return;
    }

   
    line = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (line == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return;
    }

    
    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        line_number++;
        
        
        trimmed_line = skip_whitespace(line);

         /* check if the line starts with a label (ends with ':') */
        label_end = strchr(trimmed_line, ':');
        if (label_end != NULL) {
            /* move past the label and any whitespace after ':' */
            trimmed_line = skip_whitespace(label_end + 1);
        }

       
        if (*trimmed_line == '\0') {
            continue;
        }

        /* check for .extern directive */
        if (strstr(trimmed_line, ".extern") == trimmed_line) {
            if (check_extern_directive(trimmed_line, label_table, line_number)) {
                error_flag = 1;
            }
        }

        /* check for .entry directive */
        else if (strstr(trimmed_line, ".entry") == trimmed_line) {
            if (check_entry_directive(trimmed_line, label_table, line_number ,&entry_head)) {
                error_flag = 1;
            }
        }
    }

    free(line);
    fclose(file);
    
    compare_label(encoding_table, label_table, external_label_table, &error_flag , &extern_head);


    /* if there are no errors, create the output files */
    if (error_flag == 0) {
        creating_output_files(filename, encoding_table, data_table, entry_head, extern_head);
    } 

    
    current_entry = entry_head;
    while (current_entry != NULL) {
        entry_for_output *next_entry = current_entry->next;
        free(current_entry);
        current_entry = next_entry;
    }
    current_extern = extern_head;
    while (current_extern != NULL) {
        extern_for_output *next_extern = current_extern->next;
        free(current_extern);
        current_extern = next_extern;
    } 

}





int check_entry_directive( char *line, LabelTable *label_table, int line_number
    ,entry_for_output **entry_head ) {

    char *start;
    char *label;
    LabelTable *current_label;
    

    
    if (label_table == NULL) {
        return 0; /* no error because the list is empty */
    }

    /* find the .entry word */
    start = strstr(line, ".entry");
    if (start == NULL) {
        return 0; /* no .entry found in the line */
    }

    /* skip .entry and any whitespace after */
    start = skip_whitespace(start + 6);

    /* find the end of the label */
    label = start;
    while (*label != ' ' && *label != '\t' && *label != '\n' && *label != '\0') {
        label++;
    }
    *label = '\0'; 

    /* check if the label exists in the LabelTable */
    current_label = label_table;
    while (current_label != NULL) {
        if (strcmp(current_label->label_name, start) == 0) {
            
            entry_for_output *new_entry = (entry_for_output *)malloc(sizeof(entry_for_output));
            if (new_entry == NULL) {
                fprintf(stderr, "Memory allocation failed for entry_for_output\n");
                return 1;
            }
            strncpy(new_entry->name, start, MAX_MACRO_NAME_LENGTH);
            new_entry->name[MAX_MACRO_NAME_LENGTH] = '\0'; 
            new_entry->position = current_label->decimal_address; /* position in the file */
            new_entry->next = NULL;

            
            if (*entry_head == NULL) {
               
                *entry_head = new_entry;
            } else {
                
                entry_for_output *current = *entry_head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = new_entry;
            }

            return 0;
        }
        current_label = current_label->next;
    }

    /* if we reach here, the label was not found in the list */
    printf("Error on line %d: label '%s' is not defined in this file.\n", line_number, start);
    return 1; /* error found */
}

int check_extern_directive( char *line, LabelTable *label_table, int line_number) {
    char *start;
    char *label;
    LabelTable *current_label;

   
    if (label_table == NULL) {
        return 0; /* no error because the list is empty */
    }

    
    start = strstr(line, ".extern");
    if (start == NULL) {
        return 0; 
    }

    
    start = skip_whitespace(start + 7);

    
    label = start;
    while (*label != ' ' && *label != '\t' && *label != '\n' && *label != '\0') {
        label++;
    }
    *label = '\0'; 

    
    current_label = label_table;
    while (current_label != NULL) {
        if (strcmp(current_label->label_name, start) == 0) {
            printf("Error on line %d: label '%s' should not be defined in this file.\n", line_number, start);
            return 1; /* error found */
        }
        current_label = current_label->next;
    }

    return 0; /* no error */
}



void compare_label(EncodingTable *encoding_head, LabelTable *label_head, ExternalLabelTable *external_label_head, int *error_flag
    , extern_for_output **extern_head) {
    EncodingTable *encoding_curr = encoding_head;
    LabelTable *label_curr;
    ExternalLabelTable *external_label_curr;
    extern_for_output *new_extern;

    while (encoding_curr != NULL) {
        /* check if machine_code is 0 (indicating this is a label) */
        if (encoding_curr->machine_code == 0) {
            int label_found = 0;

            /* search in the LabelTable */
            label_curr = label_head;
            while (label_curr != NULL) {
                if (strcmp(encoding_curr->name, label_curr->label_name) == 0) {
                    label_found = 1;

                    /* if no errors are found, update machine_code */
                    if (*error_flag == 0) {
                        encoding_curr->machine_code |= (label_curr->decimal_address << 3); /* Shift 2 bits to the left */
                        encoding_curr->machine_code |= (1 << 1); /* set bit 1 (R) */
                        
                    }
                    break;
                }
                label_curr = label_curr->next;
            }

             /* if no match is found in LabelTable */
            if (!label_found) {
                int external_label_found = 0;

                /* search in the ExternalLabelTable */
                external_label_curr = external_label_head;
                while (external_label_curr != NULL) {
                    if (strcmp(encoding_curr->name, external_label_curr->name) == 0) {
                        external_label_found = 1;

                        /* if no errors are found, set bit 0 (E bit) */
                        if (*error_flag == 0) {
                            encoding_curr->machine_code |= (1 << 0); /* set bit 0 (E) */

                            /* add to extern_for_output list */
                            new_extern = (extern_for_output *)malloc(sizeof(extern_for_output));
                            if (new_extern == NULL) {
                                fprintf(stderr, "Memory allocation failed for extern_for_output\n");
                                *error_flag = 1;
                                break;
                            }
                            strncpy(new_extern->name, encoding_curr->name, MAX_MACRO_NAME_LENGTH);
                            new_extern->name[MAX_MACRO_NAME_LENGTH] = '\0'; 
                            new_extern->position = encoding_curr->decimal_address; /* position in the file */
                            new_extern->next = NULL;

                            
                            if (*extern_head == NULL) {
                                *extern_head = new_extern;
                            } else {
                                extern_for_output *current = *extern_head;
                                while (current->next != NULL) {
                                    current = current->next;
                                }
                                current->next = new_extern;
                            }
                       }
                        break;
                    }
                    external_label_curr = external_label_curr->next;
                }

                /* if no match is found in either table */
                if (!external_label_found) {
                    
                    printf("Error in line %d: Operand '%s' is invalid.\n", encoding_curr->number_line_s, encoding_curr->name);
                    *error_flag = 1;
                }
            }
        }

        
        encoding_curr = encoding_curr->next;
    }
}
