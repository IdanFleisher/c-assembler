#include "convert_to_machine_code.h"
#include "compile.h"
#include "compile_two_operand.h"

void convert_to_machine_code(int exists_error, int has_label, int *data_counter,int line_number ,char *line, 
LabelTable **label_head, EncodingTable **encoding_head, DataTable **data_head
,ExternalLabelTable **extern_head, InternalLabelTable **entry_head) {
   
    LabelTable *new_label;
    char *label_name;
    LabelTable *current;

    /* check if there is an error */
    if (exists_error) {
        return;  /* stop further processing */
    }

    /* check if a label exists */
    if (has_label) {
        new_label = (LabelTable *)malloc(sizeof(LabelTable));
        
        if (new_label == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        /* extract the label name (first word before ':') */
        label_name = strtok(line, ":");
        if (label_name != NULL) {
            strncpy(new_label->label_name, label_name, MAX_MACRO_NAME_LENGTH);
            new_label->label_name[MAX_MACRO_NAME_LENGTH - 1] = '\0';  

            /* assign the data_counter to decimal_address */
            new_label->decimal_address = *data_counter;
            new_label->next = NULL;

            /* add the new label to the end of the linked list */
            if (*label_head == NULL) {
                *label_head = new_label;
            } else {
                current = *label_head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = new_label;
            }

            
            /* move to the next part of the line after the label */
            line = strtok(NULL, "");  /* continue with rest of the line */
            line = skip_whitespace(line);  /* skip whitespace */
        } else {
            printf("Invalid label format.\n");
            return;  /* nnvalid label, stop processing */
        }
    }
    line = skip_whitespace(line);  
    /* calls for functions in order to compile the correct command/instruction and their operands */
    if (strncmp(line, "stop", 4) == 0) {
        compile_stop_instruction(encoding_head, data_counter ,line_number);
    }
   
    else if (strncmp(line, "rts", 3) == 0) {
        compile_rts_instruction(encoding_head, data_counter,line_number);

    }else if (strncmp(line, "jsr", 3) == 0) {
       
        compile_jsr_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "bne", 3) == 0) {
        
        compile_bne_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "jmp", 3) == 0) {
        
        compile_jmp_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "red", 3) == 0) {
       
        compile_red_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "dec", 3) == 0) {
        
        compile_dec_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "inc", 3) == 0) {
       
        compile_inc_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "not", 3) == 0) {
        
        compile_not_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "clr", 3) == 0) {
      
        compile_clr_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "prn", 3) == 0) {
        
        compile_prn_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "mov", 3) == 0) {
        
        compile_mov_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "cmp", 3) == 0) {
       
        compile_cmp_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "add", 3) == 0) {
       
        compile_add_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "sub", 3) == 0) {
       
        compile_sub_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, "lea", 3) == 0) {
        
        compile_lea_instruction(encoding_head, data_counter, line,line_number);

    }else if (strncmp(line, ".string", 7) == 0) {
        
        compile_string_instruction(data_head, data_counter, line);

    }else if (strncmp(line, ".data", 5) == 0) {
        
        compile_data_instruction(data_head, data_counter, line);

    }else if (strncmp(line, ".entry", 6) == 0) {
       
        compile_entry_instruction(entry_head, data_counter, line);

    }else if (strncmp(line, ".extern", 7) == 0) {
       
        compile_extern_instruction(extern_head, data_counter, line);
    }

    
}



