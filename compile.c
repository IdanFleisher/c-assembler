#include "compile.h"


void compile_stop_instruction(EncodingTable **encoding_head, int *data_counter, int line_number) {
    unsigned short machine_code = 0;
    EncodingTable *new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));

    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }

    strncpy(new_encoding->name, "stop", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    machine_code |= (15 << 11);
    machine_code |= (1 << 2);
    new_encoding->machine_code = machine_code;


    (*data_counter)++;
    add_encoding_to_list(encoding_head, new_encoding);
}

void compile_rts_instruction(EncodingTable **encoding_head, int *data_counter , int line_number) {
    unsigned short machine_code = 0;
    EncodingTable *new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));

    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }

    strncpy(new_encoding->name, "rts", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0';

    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    machine_code |= (14 << 11);
    machine_code |= (1 << 2);
    new_encoding->machine_code = machine_code;


    (*data_counter)++;
    add_encoding_to_list(encoding_head, new_encoding);
}




void compile_jsr_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    ,int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
    /* allocate memory for the new encoding */

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
    
    strncpy(new_encoding->name, "jsr", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; /* ensure null termination */

    
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    

    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++; /* move past the space/tab */
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; /* skip any additional spaces/tabs */
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'jsr' in line.\n");
        return;
    }


    /* check if the operand is a valid indirect register addressing */
    if (Indirect_register_addressing(operand) == 0) {
        /*  bits 11-14 to the opcode for 'jsr'  */
        machine_code |= (13 << 11);


        /* bit 5 in bits 3-6 for addressing mode 2 in destination operand */
        machine_code |= (1 << 5); 

        /* bits 0-2 to 'A'*/
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;

      

        /* add the new encoding to the encoding list */
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    } else {
        /* bits 11-14 to the opcode for 'jsr' */
        machine_code |= (13 << 11);


        /* bit 4 in bits 3-6 for addressing mode 1 in destination operand */
        machine_code |= (1 << 4); 

        /* Set bits 0-2 to 'A' */
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

       
        add_encoding_to_list(encoding_head, new_encoding);
     
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}



void compile_bne_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    ,int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
    

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
  
    strncpy(new_encoding->name, "bne", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

   
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;

   
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++; 
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'bne' in line.\n");
        return;
    }


    /* check if the operand is a valid indirect register addressing */
    if (Indirect_register_addressing(operand) == 0) {

       
        machine_code |= (10 << 11);

        
        machine_code |= (1 << 5); 

        
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;

      

        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    } else {
        
        machine_code |= (10 << 11);

        

        
        machine_code |= (1 << 4); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

       
       
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}




void compile_jmp_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    ,int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
    

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
   
    strncpy(new_encoding->name, "jmp", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

    
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++; 
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'jmp' in line.\n");
        return;
    }


    /* Check if the operand is a valid indirect register addressing */
    if (Indirect_register_addressing(operand) == 0) {

        
        machine_code |= (9 << 11);

        

        
        machine_code |= (1 << 5); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

       

        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    } else {
       
        machine_code |= (9 << 11);


        
        machine_code |= (1 << 4); 

       
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;

        
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}



void compile_red_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    ,int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
  

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
    
    strncpy(new_encoding->name, "red", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

    
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
   
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++; 
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'red' in line.\n");
        return;
    }


    /* check if the operand is a valid indirect register addressing */
    if (Indirect_register_addressing(operand) == 0) {

       
        machine_code |= (11 << 11);

        

       
        machine_code |= (1 << 5); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;


        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    }else if (Direct_register_addressing(operand) == 0) {

       
        machine_code |= (11 << 11);


        
        machine_code |= (1 << 6); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

       

        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_3_target(encoding_head, operand, data_counter);

    } else {
       
        machine_code |= (11 << 11);

       
        machine_code |= (1 << 4); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

     
        
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}


void compile_dec_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    , int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
    

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
    
    strncpy(new_encoding->name, "dec", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

    
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++; 
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'dec' in line.\n");
        return;
    }


    /* check if the operand is a valid indirect register addressing */
    if (Indirect_register_addressing(operand) == 0) {

       
        machine_code |= (8 << 11);

       
        machine_code |= (1 << 5); 

        
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;

        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    }else if (Direct_register_addressing(operand) == 0) {

        
        machine_code |= (8 << 11);

       

       
        machine_code |= (1 << 6); 

        
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;


        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_3_target(encoding_head, operand, data_counter);

    } else {
       
        machine_code |= (8 << 11);

        

        
        machine_code |= (1 << 4); 

       
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;

        
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}


void compile_inc_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    , int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
    

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
    
    strncpy(new_encoding->name, "inc", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

    
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
   
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++; 
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'inc' in line.\n");
        return;
    }


    /* Check if the operand is a valid indirect register addressing */
    if (Indirect_register_addressing(operand) == 0) {

        
        machine_code |= (7 << 11);

        

      
        machine_code |= (1 << 5); 

        
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;


       
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    }else if (Direct_register_addressing(operand) == 0) {

       
        machine_code |= (7 << 11);

      
        machine_code |= (1 << 6); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;


       
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_3_target(encoding_head, operand, data_counter);

    } else {
       
        machine_code |= (7 << 11);

        

       
        machine_code |= (1 << 4); 

      
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;


       
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}


void compile_not_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    , int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
    

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
   
    strncpy(new_encoding->name, "not", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

   
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;

    
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++;
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'not' in line.\n");
        return;
    }


    /* Check if the operand is a valid indirect register addressing */
    if (Indirect_register_addressing(operand) == 0) {

        
        machine_code |= (6 << 11);

        

      
        machine_code |= (1 << 5); 

        
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

 
        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    }else if (Direct_register_addressing(operand) == 0) {

        
        machine_code |= (6 << 11);

        
        machine_code |= (1 << 6); 

        
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

 
       
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_3_target(encoding_head, operand, data_counter);

    } else {
        
        machine_code |= (6 << 11);

        

        
        machine_code |= (1 << 4); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

 
        
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}



void compile_clr_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
    , int line_number ) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
   

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
    
    strncpy(new_encoding->name, "clr", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 

    
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
   
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++; 
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'clr' in line.\n");
        return;
    }


   
    if (Indirect_register_addressing(operand) == 0) {

        
        machine_code |= (5 << 11);

       

       
        machine_code |= (1 << 5); 

        
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    }else if (Direct_register_addressing(operand) == 0) {

       
        machine_code |= (5 << 11);

        
        machine_code |= (1 << 6); 

        
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;

 
        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_3_target(encoding_head, operand, data_counter);

    } else {
        
        machine_code |= (5 << 11);

        

      
        machine_code |= (1 << 4); 

        
        machine_code |= (1 << 2); 

       
        new_encoding->machine_code = machine_code;


       
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}


void compile_prn_instruction(EncodingTable **encoding_head, int *data_counter, char *operand
        , int line_number) {

    unsigned short machine_code = 0;
    EncodingTable *new_encoding;
    char *next_word = strchr(operand, ' ');
   

    new_encoding = (EncodingTable *)malloc(sizeof(EncodingTable));
    if (new_encoding == NULL) {
        printf("Memory allocation failed for encoding.\n");
        return;
    }
    
    strncpy(new_encoding->name, "prn", MAX_MACRO_NAME_LENGTH);
    new_encoding->name[MAX_MACRO_NAME_LENGTH - 1] = '\0'; 
   
    new_encoding->decimal_address = *data_counter;
    new_encoding->number_line_s = line_number;
    
    (*data_counter)++;
    
    if (next_word == NULL) {
        next_word = strchr(operand, '\t');
    }
    if (next_word != NULL) {
        next_word++;
        while (*next_word == ' ' || *next_word == '\t') {
            next_word++; 
        }
        operand = next_word;
    } else {
        printf("Error: Operand not found after 'prn' in line.\n");
        return;
    }


   
    if (Indirect_register_addressing(operand) == 0) {

       
        machine_code |= (12 << 11);

        
        machine_code |= (1 << 5); 

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;


       
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_2_target(encoding_head, operand, data_counter);

    }else if (Direct_register_addressing(operand) == 0) {

       
        machine_code |= (12 << 11);

        

       
        machine_code |= (1 << 6);

       
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;
      
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_3_target(encoding_head, operand, data_counter);

    }else if (Instant_addressing(operand) == 0) {

        
        machine_code |= (12 << 11);

        
        machine_code |= (1 << 3); 

      
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;

 
        
        add_encoding_to_list(encoding_head, new_encoding);

        compile_addressing_method_0(encoding_head, operand, data_counter);

    } else {
        
        machine_code |= (12 << 11);

        
        machine_code |= (1 << 4); 

        
        machine_code |= (1 << 2); 

        
        new_encoding->machine_code = machine_code;


     
        add_encoding_to_list(encoding_head, new_encoding);
        
        compile_addressing_method_1(encoding_head, operand, data_counter ,line_number);
    }
}




