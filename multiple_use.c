#include "multiple_use.h"


int is_letter(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}


 char *skip_whitespace( char *str) {
    if (str == NULL) {
        return NULL; /* return NULL if str is NULL*/
    }

    while (*str == ' ' || *str == '\t') {
        str++;
    }
    return str;
}


int starts_with( char *str,  char *keyword) {
    return strncmp(str, keyword, strlen(keyword)) == 0;
}

/* duplicate a string safely */
char *strdup_safe( char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup == NULL) {
        return NULL;
    }
    memcpy(dup, s, len);
    return dup;
}

/* open a file and check for errors */
FILE *open_file( char *filename,  char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}





int check_first_char(char *line) {
    char *start = skip_whitespace(line);

    if (is_letter(*start) || *start == '.') {
        return 0; 
    } 
     else {
        return 1; 
    }
}











int check_word_colon(char *line) {
    char *start = skip_whitespace(line);

   
    while (isalnum((unsigned char)*start) || *start == '_') {
        start++;
    }

    
    if (*start == ':') {
        return 1; 
    }

    return 0; 
}










int check_hash_no_whitespace(char *line) {
    char *hash_pos = strchr(line, '#');
    if (hash_pos != NULL && *(hash_pos + 1) != ' ' && *(hash_pos + 1) != '\t') {
        return 1; /* '#' is followed by a non whitespace character */
    }
    return 0; /* either '#' is not present or it is followed by whitespace */
}










int check_star_not_followed_by_register(char *line) {


char *end;
    char *star_pos = strchr(line, '*');
    if (star_pos != NULL) {
        char *after_star = skip_whitespace(star_pos + 1);

    /* remove trailing newline or other whitespace characters if present*/
    size_t len = strlen(after_star);
    if (len > 0) {
        
        end = after_star + len - 1;

        
        while (end > after_star && (*end == '\n' || *end == '\t' || *end == ' ')) {
        end--;
        }

       
        *(end + 1) = '\0';
    }

        if (strcmp(after_star, R0) != 0 &&
            strcmp(after_star, R1) != 0 &&
            strcmp(after_star, R2) != 0 &&
            strcmp(after_star, R3) != 0 &&
            strcmp(after_star, R4) != 0 &&
            strcmp(after_star, R5) != 0 &&
            strcmp(after_star, R6) != 0 &&
            strcmp(after_star, R7) != 0) {
            return 0; /* '*' is not followed by a valid register */
        }
    }
    return 1; /* '*' is followed by a valid register */
}






/* check if a word is a reserved keyword */
int is_reserved_word(char *word) {
     char *reserved_words[] = {
        "mov", "add", "sub", "lea", "jmp", "cmp", "clr", "not", "inc", "dec",
        "bne", "red", "prn", "jsr", "rts", "stop", ".data", ".string", 
        ".entry", ".extern" };

    int i;
    int num_reserved_words = sizeof(reserved_words) / sizeof(reserved_words[0]);
    for (i = 0; i < num_reserved_words; i++) {
        if (strcmp(word, reserved_words[i]) == 0) {
            return 1; /* the word is a reserved keyword*/
        }
    }
    return 0; /* the word is not a reserved keyword*/
}








int is_valid_register(char *word) {
    char *registers[] = { R0, R1, R2, R3, R4, R5, R6, R7};
    int i;
    int num_registers = sizeof(registers) / sizeof(registers[0]);

    for ( i = 0; i < num_registers; i++) {
        if (strcmp(word, registers[i]) == 0) {
            return 1; /* the word is a valid register*/
        }
    }
    return 0; /* the word is not a valid register*/
}






int is_first_char_special(char *line) {
char first_char;

    if (line == NULL || line[0] == '\0') {
        return 0; /* line is empty */
    }
    


    first_char = line[0];

    if (first_char == '\n' || first_char == ' ' || first_char == '\t') {
        return 1; /* the first character is one of the special characters */
    }

    return 0; /* the first character is not one of the special characters */
}




















