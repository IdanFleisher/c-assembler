#include "validate_code.h"

int check_non_operand_instructions(char *line, int line_number) {
    char *word = line;

    /* check if the line starts with 'stop' or 'rts' */
    if (strncmp(word, "stop", 4) == 0) {
        word += 4;
    } else if (strncmp(word, "rts", 3) == 0) {
        word += 3;
    } else {
        return 0;  /* no error, since the line doesn't start with 'stop' or 'rts' */
    }

 	if (!isspace(*word)) {
        fprintf(stderr, "Error in line %d: is not a valid directive or command\n", line_number);
        return 1;
    }
   word = skip_whitespace(word);


    
    /* check if there are non whitespace characters after 'stop' or 'rts' */
    if (*word != '\0' && *word != '\n') {
        fprintf(stderr, "Error in line %d: The keyword '%.*s' must not have any arguments or characters following it.\n",
                line_number, (int)(word - line), line);
        return 1;
    }

    return 0;  
}



int check_one_operand_instructions(char *line, int line_number) {
    char *keywords[] = {
        "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr"
    };
    int keyword_count = sizeof(keywords) / sizeof(keywords[0]);
    char *word_start = skip_whitespace(line);
    int i;
    char *operand_start;

    for (i = 0; i < keyword_count; i++) {
        if (strncmp(word_start, keywords[i], strlen(keywords[i])) == 0) {
            
            /* skip the keyword */
            word_start += strlen(keywords[i]);

 	if (!isspace(*word_start)) {
        fprintf(stderr, "Error in line %d: is not a valid directive or command\n", line_number);
        return 1;
    }
            word_start = skip_whitespace(word_start);

            /* check for the first operand */
            operand_start = word_start;
            while (!isspace(*word_start) && *word_start != '\0') {
                word_start++;
            }

            /* if we didn't find any operand */
            if (operand_start == word_start) {
                fprintf(stderr, "Error in line %d: Instruction '%s' must have exactly one operand, but none was found.\n", line_number, keywords[i]);
                return 1;
            }

            /* skip whitespace after the operand */
            word_start = skip_whitespace(word_start);

            /* if there's another non whitespace character after the operand, it's an error */
            if (*word_start != '\0' && *word_start != '\n') {
                fprintf(stderr, "Error in line %d: Instruction '%s' must have exactly one operand, but more were found.\n", line_number, keywords[i]);
                return 1;
            }

            return 0; /* no error if there's exactly one operand */
        }
    }

    return 0;  /* no specific keyword found */

}




int check_two_operand_instructions(char *line, int line_number) {
    
    char *keywords[] = {
        "mov", "cmp", "add", "sub", "lea"
    };
    int keyword_count = sizeof(keywords) / sizeof(keywords[0]);
    char *word_start;
    int i;
    char *first_operand_start;
    char *second_operand_start;

    word_start = skip_whitespace(line);

    for (i = 0; i < keyword_count; i++) {
        if (strncmp(word_start, keywords[i], strlen(keywords[i])) == 0) {
            

            
            word_start += strlen(keywords[i]);
  if (!isspace(*word_start)) {
        fprintf(stderr, "Error in line %d: is not a valid directive or command\n", line_number);
        return 1;
    }
            word_start = skip_whitespace(word_start);

            /* check for the first operand */
            first_operand_start = word_start;
            while (!isspace(*word_start) && *word_start != '\0' && *word_start != ',') {
                word_start++;
            }

            /* if we didn't find any first operand */
            if (first_operand_start == word_start) {
                fprintf(stderr, "Error in line %d: Instruction '%s' must have exactly two operands, but the first operand was not found.\n", line_number, keywords[i]);
                return 1;
            }

            /* skip whitespace after the first operand */
            word_start = skip_whitespace(word_start);

            /* check if there is a comma */
            if (*word_start != ',') {
                fprintf(stderr, "Error in line %d: Instruction '%s' must have a comma separating two operands.\n", line_number, keywords[i]);
                return 1;
            }

            /* skip the comma and any whitespace */
            word_start++;
            word_start = skip_whitespace(word_start);

            /* check for the second operand */
            second_operand_start = word_start;
            while (!isspace(*word_start) && *word_start != '\0') {
                word_start++;
            }

            /* if we didn't find a second operand */
            if (second_operand_start == word_start) {
                fprintf(stderr, "Error in line %d: Instruction '%s' must have exactly two operands, but the second operand was not found.\n", line_number, keywords[i]);
                return 1;
            }

            /* skip any whitespace after the second operand */
            word_start = skip_whitespace(word_start);

            /* if there's another non whitespace character after the second operand, it's an error */
            if (*word_start != '\0' && *word_start != '\n') {
                fprintf(stderr, "Error in line %d: Instruction '%s' must have exactly two operands, but more were found.\n", line_number, keywords[i]);
                return 1;
            }

            return 0; /* no error if there are exactly two operands */
        }
    }

    return 0;  /* no specific keyword found */
}




int check_data_directive(char *line, int line_number) {
    char *word_start;
    int expecting_number;

    
    word_start = skip_whitespace(line);

    /* check if the line starts with ".data" */
    if (!starts_with(word_start, ".data")) {
        return 0;  /* not a .data directive, no error */
    }

    /* skip over ".data" */
    word_start += 5;

    if (!isspace(*word_start)) {
        fprintf(stderr, "Error in line %d: is not a valid directive or command\n", line_number);
        return 1;
    }

    
    word_start = skip_whitespace(word_start);

    /* check if the first character after ".data" is a digit or a '-' for negative numbers */
    if (*word_start != '-' && !isdigit(*word_start)) {
        fprintf(stderr, "Error in line %d: .data directive must be followed by at least one integer.\n", line_number);
        return 1;
    }

    expecting_number = 1;  /* 1 if expecting a number, 0 if expecting a comma */
    while (*word_start != '\0' && *word_start != '\n') {
        if (expecting_number) {
            /* if there is a - sign, check the next character */
            if (*word_start == '-') {
                word_start++;
                if (!isdigit(*word_start)) {
                    fprintf(stderr, "Error in line %d: '-' must be followed by a number.\n", line_number);
                    return 1;
                }
            }

            /* expect a number */
            if (!isdigit(*word_start)) {
                fprintf(stderr, "Error in line %d: Expected a number but found '%c'.\n", line_number, *word_start);
                return 1;
            }

            /* skip the number */
            while (isdigit(*word_start)) {
                word_start++;
            }

            /* skip any whitespace after the number */
            word_start = skip_whitespace(word_start);

            /* after a number, expect a comma or end of line */
            expecting_number = 0;
        } else {
            /* expect a comma */
            if (*word_start != ',') {
                fprintf(stderr, "Error in line %d: Numbers in .data directive must be separated by a comma.\n", line_number);
                return 1;
            }

            /* skip the comma and any whitespace */
            word_start++;
            word_start = skip_whitespace(word_start);

            /* ensure the nextcharacter after the comma is a number or a '-' */
            if (*word_start != '-' && !isdigit(*word_start)) {
                fprintf(stderr, "Error in line %d: Expected a number after the comma in .data directive.\n", line_number);
                return 1;
            }

            expecting_number = 1;
        }
        word_start = skip_whitespace(word_start);
    }

    /* check if the line ends correctly */
    if (*word_start == ',' || expecting_number) {
        fprintf(stderr, "Error in line %d: .data directive cannot end with a comma.\n", line_number);
        return 1;
    }

    return 0;  /* No error */
}












int check_string_directive(char *line, int line_number) {
    char *word_start;
    int expecting_string;

    
    word_start = skip_whitespace(line);

    /*check if the line starts with ".string" */
    if (!starts_with(word_start, ".string")) {
        return 0;  /* Not a .string directive, no error */
    }

    /* skip over ".string" */
    word_start += 7;


    /* check if word is correct */
    
    if (!isspace(*word_start)) {
        fprintf(stderr, "Error in line %d: is not a valid directive or command\n", line_number);
        return 1;
    }

    
    word_start = skip_whitespace(word_start);
   
    /* ensure there's something after the whitespaces */
    /*if there is a white space after .string but nothing other then that it will print*/
    if (*word_start == '\0' || *word_start == '\n') {
        fprintf(stderr, "Error in line %d: Missing string after '.string' directive.\n", line_number);
        return 1;
    }


    /* now expect a string */
    expecting_string = 1;

    while (*word_start != '\0' && *word_start != '\n') {
        if (expecting_string) {
            /* expect a string starting with a " */
            if (*word_start != '"') {
                fprintf(stderr, "Error in line %d: Expected a string starting with a quote but found '%c'.\n", line_number, *word_start);
                return 1;
            }

            /* skip the opening " */
            word_start++;

            /* skip the string content */
            while (*word_start != '"' && *word_start != '\0' && *word_start != '\n') {
                word_start++;
            }

            /* check if the string ends with a " */
            if (*word_start != '"') {
                fprintf(stderr, "Error in line %d: String must end with a quote.\n", line_number);
                return 1;
            }

            /* skip the closing quote */
            word_start++;
            word_start = skip_whitespace(word_start);

            /* after a string, expect a comma or end of line */
            expecting_string = 0;
        } else {
            /* expect comma */
            if (*word_start != ',') {
                fprintf(stderr, "Error in line %d: Strings in .string directive must be separated by a comma.\n", line_number);
                return 1;
            }

            /* skip the comma and whitespaces */
            word_start++;
            word_start = skip_whitespace(word_start);

            /* ensure the next character after the comma is a string starting with a " */
            if (*word_start != '"') {
                fprintf(stderr, "Error in line %d: Expected a string after the comma in .string directive.\n", line_number);
                return 1;
            }

            expecting_string = 1;
        }
    }

    
    /* check if the line ends correctly */
    if (expecting_string) {
        fprintf(stderr, "Error in line %d: .string directive must contain a valid string after each comma.\n", line_number);
        return 1;
    }
    
    return 0;  /* No error */
}



int check_entry_and_extern_directive(char *line, int line_number) {
    char *word_start;
    char *reserved_words[] = {
        "mov", "add", "sub", "lea", "jmp", "cmp", "clr", "not", "inc", "dec", 
        "bne", "red", "prn", "jsr", "rts", "stop", ".data", ".string", 
        ".entry", ".extern", R0, R1, R2, R3, R4, R5, R6, R7};

    /* instead of index so will be easy to add or subtract words in array*/
    int reserved_word_count = sizeof(reserved_words) / sizeof(reserved_words[0]);
    int i;
    char *label_start;

    word_start = skip_whitespace(line);

    /* check if the line starts with .entry or .extern */
    if (!starts_with(word_start, ".entry") && !starts_with(word_start, ".extern")) {
        return 0;  /* not an .entry or .extern directive, no error */
    }

    /* skip over .entry or .extern */
    word_start += starts_with(word_start, ".entry") ? 6 : 7;


   if (!isspace(*word_start)) {
        fprintf(stderr, "Error in line %d: is not a valid directive or command\n", line_number);
        return 1;
    }

    word_start = skip_whitespace(word_start);

    /* check if there is at least one whitespace after .entry or .extern */
    if (*word_start == '\0' || *word_start == '\n') {
        fprintf(stderr, "Error in line %d: %s directive must be followed by a label.\n", line_number, starts_with(line, ".entry") ? ".entry" : ".extern");
        return 1;
    }

    /* ensure there's only one label (or word) after .entry or .extern */
   label_start = word_start;
    while (!isspace(*word_start) && *word_start != '\0' && *word_start != '\n') {
        word_start++;
    }

    /* check if the label is a reserved word (command, directive, or register) */
    for (i = 0; i < reserved_word_count; i++) {
        if (strncmp(label_start, reserved_words[i], strlen(reserved_words[i])) == 0) {
            fprintf(stderr, "Error in line %d: '%s' is a reserved word and cannot be used as a label.\n", line_number, reserved_words[i]);
            return 1;
        }
    }

    word_start = skip_whitespace(word_start);

    /* check if there's any other non-whitespace character after the label */
    if (*word_start != '\0' && *word_start != '\n') {
        fprintf(stderr, "Error in line %d: %s directive must have only one label, but found extra characters.\n", line_number, starts_with(line, ".entry") ? ".entry" : ".extern");
        return 1;
    }

    return 0;
}





