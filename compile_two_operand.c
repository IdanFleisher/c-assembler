#include "compile_two_operand.h"



void compile_mov_instruction(EncodingTable **encoding_head, int *data_counter, char *operands,
        int line_number) {
    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *comma_pos;
    char *target_operand;
    int flag_source, flag_target;
    char source_operand[MAX_MACRO_NAME_LENGTH];

   
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }

   
    strncpy(new_encoding->name, "mov", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    
    (*data_counter)++;

   
    machine_code |= (0 << 11);

   
    operands = strchr(operands, ' ');
    if (operands == NULL) {
        printf("Error: Invalid format, no operands found after 'mov'.\n");
        free(new_encoding);
        return;
    }

    
    operands = skip_whitespace(operands);

   
    comma_pos = strchr(operands, ',');
    if (comma_pos == NULL) {
        printf("Error: Invalid format, operands are not separated by a comma.\n");
        free(new_encoding);
        return;
    }

    
    strncpy(source_operand, operands, comma_pos - operands);
    source_operand[comma_pos - operands] = '\0';

    
    target_operand = skip_whitespace(comma_pos + 1);

    
    if (Instant_addressing(source_operand) == 0) {
        flag_source = 0;
    } else if (Indirect_register_addressing(source_operand) == 0) {
        flag_source = 2;
    } else if (Direct_register_addressing(source_operand) == 0) {
        flag_source = 3;
    } else {
        flag_source = 1;
    }

    
    if (Indirect_register_addressing(target_operand) == 0) {
        flag_target = 2;
    } else if (Direct_register_addressing(target_operand) == 0) {
        flag_target = 3;
    } else {
        flag_target = 1;
    }

   
    if (flag_source == 0) {
        machine_code |= (1 << 7);
    } else if (flag_source == 1) {
        machine_code |= (1 << 8);
    } else if (flag_source == 2) {
        machine_code |= (1 << 9);
    } else if (flag_source == 3) {
        machine_code |= (1 << 10);
    }

    
    if (flag_target == 1) {
        machine_code |= (1 << 4);
    } else if (flag_target == 2) {
        machine_code |= (1 << 5);
    } else if (flag_target == 3) {
        machine_code |= (1 << 6);
    }

   
    machine_code |= (1 << 2);

    
    new_encoding->machine_code = machine_code;

    
    add_encoding_to_list(encoding_head, new_encoding);

    if (flag_source == flag_target && flag_source ==2)
    {
        shared_code_word_method_2(encoding_head, source_operand ,target_operand, data_counter);
    }
    else if (flag_source == flag_target && flag_source ==3)
    {
        shared_code_word_method_3(encoding_head, source_operand ,target_operand, data_counter);
    }
    else{
        if (flag_source==0)
        {
            compile_addressing_method_0(encoding_head, source_operand, data_counter);
        }else if (flag_source==1)
        {
            compile_addressing_method_1(encoding_head, source_operand, data_counter ,line_number);
        }else if (flag_source==2)
        {
            compile_addressing_method_2_source(encoding_head, source_operand, data_counter);
        }else{
            compile_addressing_method_3_source(encoding_head, source_operand, data_counter);
        }

        if (flag_target==1)
        {
            compile_addressing_method_1(encoding_head, target_operand, data_counter, line_number);
        }else if (flag_target==2)
        {
            compile_addressing_method_2_target(encoding_head, target_operand, data_counter);
        }else{
            compile_addressing_method_3_target(encoding_head, target_operand, data_counter);
        }    
    }
}


void compile_cmp_instruction(EncodingTable **encoding_head, int *data_counter, char *operands
    ,int line_number) {
    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *comma_pos;
    char *target_operand;
    int flag_source, flag_target;
    char source_operand[MAX_MACRO_NAME_LENGTH];

   
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }

    
    strncpy(new_encoding->name, "cmp", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    
    (*data_counter)++;

    
    machine_code |= (1 << 11);

    
    operands = strchr(operands, ' ');
    if (operands == NULL) {
        printf("Error: Invalid format, no operands found after 'cmp'.\n");
        free(new_encoding);
        return;
    }

    
    operands = skip_whitespace(operands);

    
    comma_pos = strchr(operands, ',');
    if (comma_pos == NULL) {
        printf("Error: Invalid format, operands are not separated by a comma.\n");
        free(new_encoding);
        return;
    }

   
    strncpy(source_operand, operands, comma_pos - operands);
    source_operand[comma_pos - operands] = '\0'; 

    
    target_operand = skip_whitespace(comma_pos + 1);

    
    if (Instant_addressing(source_operand) == 0) {
        flag_source = 0;
    } else if (Indirect_register_addressing(source_operand) == 0) {
        flag_source = 2;
    } else if (Direct_register_addressing(source_operand) == 0) {
        flag_source = 3;
    } else {
        flag_source = 1;
    }

   
    if (Instant_addressing(target_operand) == 0) {
        flag_target = 0;
    } else if (Indirect_register_addressing(target_operand) == 0) {
        flag_target = 2;
    } else if (Direct_register_addressing(target_operand) == 0) {
        flag_target = 3;
    } else {
        flag_target = 1;
    }

    
    if (flag_source == 0) {
        machine_code |= (1 << 7);
    } else if (flag_source == 1) {
        machine_code |= (1 << 8);
    } else if (flag_source == 2) {
        machine_code |= (1 << 9);
    } else if (flag_source == 3) {
        machine_code |= (1 << 10);
    }

    
    if (flag_target == 0) {
        machine_code |= (1 << 3);
    } else if (flag_target == 1) {
        machine_code |= (1 << 4);
    } else if (flag_target == 2) {
        machine_code |= (1 << 5);
    } else if (flag_target == 3) {
        machine_code |= (1 << 6);
    }

    
    machine_code |= (1 << 2);

    
    new_encoding->machine_code = machine_code;

   
    add_encoding_to_list(encoding_head, new_encoding);

    if (flag_source == flag_target && flag_source ==2)
    {
        shared_code_word_method_2(encoding_head, source_operand ,target_operand, data_counter);
    }
    else if (flag_source == flag_target && flag_source ==3)
    {
        shared_code_word_method_3(encoding_head, source_operand ,target_operand, data_counter);
    }
    else{
        if (flag_source==0)
        {
            compile_addressing_method_0(encoding_head, source_operand, data_counter);
        }else if (flag_source==1)
        {
            compile_addressing_method_1(encoding_head, source_operand, data_counter ,line_number);
        }else if (flag_source==2)
        {
            compile_addressing_method_2_source(encoding_head, source_operand, data_counter);
        }else{
            compile_addressing_method_3_source(encoding_head, source_operand, data_counter);
        }



        
        if (flag_target==0)
        {
            compile_addressing_method_0(encoding_head, target_operand, data_counter);
        }else if (flag_target==1)
        {
            compile_addressing_method_1(encoding_head, target_operand, data_counter, line_number);
        }else if (flag_target==2)
        {
            compile_addressing_method_2_target(encoding_head, target_operand, data_counter);
        }else{
            compile_addressing_method_3_target(encoding_head, target_operand, data_counter);
        }
        
        
    }
}



void compile_add_instruction(EncodingTable **encoding_head, int *data_counter, char *operands
    , int line_number) {
    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *comma_pos;
    char *target_operand;
    int flag_source, flag_target;
    char source_operand[MAX_MACRO_NAME_LENGTH];

  
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }

    
    strncpy(new_encoding->name, "add", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
   
    (*data_counter)++;

    
    machine_code |= (2 << 11);

   
    operands = strchr(operands, ' ');
    if (operands == NULL) {
        printf("Error: Invalid format, no operands found after 'add'.\n");
        free(new_encoding);
        return;
    }

    
    operands = skip_whitespace(operands);

   
    comma_pos = strchr(operands, ',');
    if (comma_pos == NULL) {
        printf("Error: Invalid format, operands are not separated by a comma.\n");
        free(new_encoding);
        return;
    }

    
    strncpy(source_operand, operands, comma_pos - operands);
    source_operand[comma_pos - operands] = '\0'; 

    
    target_operand = skip_whitespace(comma_pos + 1);

   
    if (Instant_addressing(source_operand) == 0) {
        flag_source = 0;
    } else if (Indirect_register_addressing(source_operand) == 0) {
        flag_source = 2;
    } else if (Direct_register_addressing(source_operand) == 0) {
        flag_source = 3;
    } else {
        flag_source = 1;
    }

    
    if (Indirect_register_addressing(target_operand) == 0) {
        flag_target = 2;
    } else if (Direct_register_addressing(target_operand) == 0) {
        flag_target = 3;
    } else {
        flag_target = 1;
    }

    
    if (flag_source == 0) {
        machine_code |= (1 << 7);
    } else if (flag_source == 1) {
        machine_code |= (1 << 8);
    } else if (flag_source == 2) {
        machine_code |= (1 << 9);
    } else if (flag_source == 3) {
        machine_code |= (1 << 10);
    }

   
    if (flag_target == 1) {
        machine_code |= (1 << 4);
    } else if (flag_target == 2) {
        machine_code |= (1 << 5);
    } else if (flag_target == 3) {
        machine_code |= (1 << 6);
    }

    
    machine_code |= (1 << 2);

   
    new_encoding->machine_code = machine_code;

   
    add_encoding_to_list(encoding_head, new_encoding);

    if (flag_source == flag_target && flag_source ==2)
    {
        shared_code_word_method_2(encoding_head, source_operand ,target_operand, data_counter);
    }
    else if (flag_source == flag_target && flag_source ==3)
    {
        shared_code_word_method_3(encoding_head, source_operand ,target_operand, data_counter);
    }
    else{
        if (flag_source==0)
        {
            compile_addressing_method_0(encoding_head, source_operand, data_counter);
        }else if (flag_source==1)
        {
            compile_addressing_method_1(encoding_head, source_operand, data_counter ,line_number);
        }else if (flag_source==2)
        {
            compile_addressing_method_2_source(encoding_head, source_operand, data_counter);
        }else{
            compile_addressing_method_3_source(encoding_head, source_operand, data_counter);
        }

        if (flag_target==1)
        {
            compile_addressing_method_1(encoding_head, target_operand, data_counter, line_number);
        }else if (flag_target==2)
        {
            compile_addressing_method_2_target(encoding_head, target_operand, data_counter);
        }else{
            compile_addressing_method_3_target(encoding_head, target_operand, data_counter);
        }    
    }
}


void compile_sub_instruction(EncodingTable **encoding_head, int *data_counter, char *operands
        , int line_number) {
    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *comma_pos;
    char *target_operand;
    int flag_source, flag_target;
    char source_operand[MAX_MACRO_NAME_LENGTH];

    
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }

    
    strncpy(new_encoding->name, "sub", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
   
    (*data_counter)++;

    
    machine_code |= (3 << 11);

    
    operands = strchr(operands, ' ');
    if (operands == NULL) {
        printf("Error: Invalid format, no operands found after 'sub'.\n");
        free(new_encoding);
        return;
    }

  
    operands = skip_whitespace(operands);

    
    comma_pos = strchr(operands, ',');
    if (comma_pos == NULL) {
        printf("Error: Invalid format, operands are not separated by a comma.\n");
        free(new_encoding);
        return;
    }

    
    strncpy(source_operand, operands, comma_pos - operands);
    source_operand[comma_pos - operands] = '\0'; 

    
    target_operand = skip_whitespace(comma_pos + 1);

    
    if (Instant_addressing(source_operand) == 0) {
        flag_source = 0;
    } else if (Indirect_register_addressing(source_operand) == 0) {
        flag_source = 2;
    } else if (Direct_register_addressing(source_operand) == 0) {
        flag_source = 3;
    } else {
        flag_source = 1;
    }

    
    if (Indirect_register_addressing(target_operand) == 0) {
        flag_target = 2;
    } else if (Direct_register_addressing(target_operand) == 0) {
        flag_target = 3;
    } else {
        flag_target = 1;
    }

   
    if (flag_source == 0) {
        machine_code |= (1 << 7);
    } else if (flag_source == 1) {
        machine_code |= (1 << 8);
    } else if (flag_source == 2) {
        machine_code |= (1 << 9);
    } else if (flag_source == 3) {
        machine_code |= (1 << 10);
    }

    
    if (flag_target == 1) {
        machine_code |= (1 << 4);
    } else if (flag_target == 2) {
        machine_code |= (1 << 5);
    } else if (flag_target == 3) {
        machine_code |= (1 << 6);
    }

    
    machine_code |= (1 << 2);

    
    new_encoding->machine_code = machine_code;

    
    add_encoding_to_list(encoding_head, new_encoding);

    if (flag_source == flag_target && flag_source ==2)
    {
        shared_code_word_method_2(encoding_head, source_operand ,target_operand, data_counter);
    }
    else if (flag_source == flag_target && flag_source ==3)
    {
        shared_code_word_method_3(encoding_head, source_operand ,target_operand, data_counter);
    }
    else{
        if (flag_source==0)
        {
            compile_addressing_method_0(encoding_head, source_operand, data_counter);
        }else if (flag_source==1)
        {
            compile_addressing_method_1(encoding_head, source_operand, data_counter ,line_number);
        }else if (flag_source==2)
        {
            compile_addressing_method_2_source(encoding_head, source_operand, data_counter);
        }else{
            compile_addressing_method_3_source(encoding_head, source_operand, data_counter);
        }

        if (flag_target==1)
        {
            compile_addressing_method_1(encoding_head, target_operand, data_counter, line_number);
        }else if (flag_target==2)
        {
            compile_addressing_method_2_target(encoding_head, target_operand, data_counter);
        }else{
            compile_addressing_method_3_target(encoding_head, target_operand, data_counter);
        }    
    }
}


void compile_lea_instruction(EncodingTable **encoding_head, int *data_counter, char *operands
    , int line_number) {
    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *comma_pos;
    char *target_operand;
    int  flag_target;
    char source_operand[MAX_MACRO_NAME_LENGTH];

   
    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }

    
    strncpy(new_encoding->name, "lea", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    
    (*data_counter)++;

    
    machine_code |= (4 << 11);

   
    operands = strchr(operands, ' ');
    if (operands == NULL) {
        printf("Error: Invalid format, no operands found after 'lea'.\n");
        free(new_encoding);
        return;
    }

   
    operands = skip_whitespace(operands);

    
    comma_pos = strchr(operands, ',');
    if (comma_pos == NULL) {
        printf("Error: Invalid format, operands are not separated by a comma.\n");
        free(new_encoding);
        return;
    }

    
    strncpy(source_operand, operands, comma_pos - operands);
    source_operand[comma_pos - operands] = '\0'; 

   
    target_operand = skip_whitespace(comma_pos + 1);


   
    if (Indirect_register_addressing(target_operand) == 0) {
        flag_target = 2;
    } else if (Direct_register_addressing(target_operand) == 0) {
        flag_target = 3;
    } else {
        flag_target = 1;
    }

    
    machine_code |= (1 << 7);

    
    if (flag_target == 1) {
        machine_code |= (1 << 4);
    } else if (flag_target == 2) {
        machine_code |= (1 << 5);
    } else if (flag_target == 3) {
        machine_code |= (1 << 6);
    }

   
    machine_code |= (1 << 2);

    
    new_encoding->machine_code = machine_code;

    add_encoding_to_list(encoding_head, new_encoding);

    /* source_operand can be only 1  -- no need to check shared word */
    compile_addressing_method_1(encoding_head, source_operand, data_counter ,line_number);
    if (flag_target==1)
    {
        compile_addressing_method_1(encoding_head, target_operand, data_counter, line_number);
    }else if (flag_target==2)
    {
        compile_addressing_method_2_target(encoding_head, target_operand, data_counter);
    }else{
        compile_addressing_method_3_target(encoding_head, target_operand, data_counter);
    }        
}



void compile_string_instruction(DataTable **data_head, int *data_counter, char *line) {
    DataTable *new_data;
    char *start;
    char *end;
    int i;

   
    new_data = (DataTable *)malloc(sizeof(DataTable));
    if (new_data == NULL) {
        printf("Memory allocation failed for data table.\n");
        return;
    }

   
    start = strstr(line, ".string");
    if (start == NULL) {
        printf("Error: No .string directive found.\n");
        free(new_data);
        return;
    }

    
    start = skip_whitespace(start + 7);

    
    if (*start != '"') {
        printf("Error: String not enclosed in quotes.\n");
        free(new_data);
        return;
    }

    
    start++;

    
    end = strchr(start, '"');
    if (end == NULL) {
        printf("Error: No closing quote found.\n");
        free(new_data);
        return;
    }

    /* iterate over each character in the string */
    for (i = 0; start[i] != '"' && start[i] != '\0'; i++) {
        new_data = (DataTable *)malloc(sizeof(DataTable));
        if (new_data == NULL) {
            printf("Memory allocation failed for data table.\n");
            return;
        }

        
        strncpy(new_data->name, &start[i], 1);
        new_data->name[1] = '\0'; 

        
        new_data->decimal_address = *data_counter;

        
        (*data_counter)++;

        /* convert the character to its ASCII value */
        new_data->machine_code = (unsigned short)start[i];


        
        add_data_to_list(data_head, new_data);
    }

    /* add the final '\0' character */
    new_data = (DataTable *)malloc(sizeof(DataTable));
    if (new_data == NULL) {
        printf("Memory allocation failed for data table.\n");
        return;
    }

    
    strcpy(new_data->name, "\\0");

    
    new_data->decimal_address = *data_counter;

    
    (*data_counter)++;

    
    new_data->machine_code = 0;

    
    add_data_to_list(data_head, new_data);
}



void compile_data_instruction(DataTable **data_head, int *data_counter, char *line) {
    DataTable *new_data;
    char *start;
    char *end;
    char number_str[MAX_MACRO_NAME_LENGTH];  /* temporary buffer to hold the number as a string */
    int number;

    
    start = strstr(line, ".data");
    if (start == NULL) {
        printf("Error: No .data directive found.\n");
        return;
    }

    
    start = skip_whitespace(start + 5);

    /* iterate over each number in the line */
    while (*start != '\0') {
        /* find the next comma or the end of the line */
        end = strchr(start, ',');
        if (end == NULL) {
            end = start + strlen(start);  
        }

        /* extract the number as a string */
        strncpy(number_str, start, end - start);
        number_str[end - start] = '\0';  

        /* convert the number string to an integer */
        number = atoi(number_str);

        
        new_data = (DataTable *)malloc(sizeof(DataTable));
        if (new_data == NULL) {
            printf("Memory allocation failed for data table.\n");
            return;
        }

        
        new_data->decimal_address = *data_counter;

        
        (*data_counter)++;

        
        new_data->machine_code = (unsigned short)number;

 
        
        add_data_to_list(data_head, new_data);

        /* move to the next number, if present */
        start = skip_whitespace(end);
        if (*start == ',') {
            start = skip_whitespace(start + 1);  
        } else {
            break;  /* no more numbers to process */
        }
    }
}




void compile_entry_instruction(InternalLabelTable **label_head, int *data_counter, char *line) {
    InternalLabelTable *new_label;
    char *start;
    char *end;

    /* skip the ".entry" word and move to the label */
    start = strstr(line, ".entry");
    if (start == NULL) {
        printf("Error: No .entry directive found.\n");
        return;
    }

    
    start = skip_whitespace(start + 6);

    /* remove any trailing whitespace or newline characters */
    end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) {
        *end = '\0';
        end--;
    }

    
    new_label = (InternalLabelTable *)malloc(sizeof(InternalLabelTable));
    if (new_label == NULL) {
        printf("Memory allocation failed for internal label table.\n");
        return;
    }

    
    strncpy(new_label->name, start, MAX_MACRO_NAME_LENGTH);
    new_label->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

    
    new_label->decimal_address = *data_counter;
    
    (*data_counter)++;

    /* add the new label to the InternalLabelTable list */
    add_internal_label_to_list(label_head, new_label);
}




void compile_extern_instruction(ExternalLabelTable **label_head, int *data_counter, char *line) {
    ExternalLabelTable *new_label;
    char *start;
    char *end;

    
    start = strstr(line, ".extern");
    if (start == NULL) {
        printf("Error: No .extern directive found.\n");
        return;
    }

    
    start = skip_whitespace(start + 7);

    
    end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) {
        *end = '\0';
        end--;
    }

    
    new_label = (ExternalLabelTable *)malloc(sizeof(ExternalLabelTable));
    if (new_label == NULL) {
        printf("Memory allocation failed for external label table.\n");
        return;
    }

    
    strncpy(new_label->name, start, MAX_MACRO_NAME_LENGTH);
    new_label->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

    
    new_label->decimal_address = *data_counter;
    
    (*data_counter)++;

    /* add the new label to the ExternalLabelTable list */
    add_external_label_to_list(label_head, new_label);
}




