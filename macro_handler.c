#include "macro_handler.h"


/* Check if the line has only the macro name with no other non-whitespace characters */
int isMacroNameAloneOnLine(char *line, char *macro_name) {
    char *start = skip_whitespace(line);
     char *found;

    /* Check if the macro name is at the start */
    found = strstr(start, macro_name);
    if (found != start) {
        return 0; /* Macro name is not alone */
    }

    /* Check if there are only whitespace characters after the macro name */
    found += strlen(macro_name);
    return (*skip_whitespace(found) == '\0'); /* Return true if only whitespace follows */
}

/* Check if a macro name is used as a label (followed by a colon) */
int isMacroNameUsedAsLabel(char *line, char *macro_name) {
     char *start = skip_whitespace(line);
     char *found;

    /* Check if the macro name is at the start */
    found = strstr(start, macro_name);
    if (found != start) {
        return 0; /* Macro name is not at the start */
    }

    /* Check for colon immediately after macro name */
    found += strlen(macro_name);
    return (*skip_whitespace(found) == ':'); /* Return true if a colon follows */
}

void handleMacroStart(char *line, Macro **macros, int *macro_count, int *macro_capacity, int *macro_flag, Macro **current_macro, int *has_error, char *filename, int line_number) {
     int error_printed = 0;
    char *token = strtok(line, " \t\n");

    /* Checks if the word 'macr' is in its correct place */
    if (!isMacrLineFormattedCorrectly(line)) {
        fprintf(stderr, "Error in file %s at line %d: 'macr' must be the first non-whitespace text in the line.\n", filename, line_number);
        *has_error = 1;
        return;
    }

    token = strtok(NULL, " \t\n");
    if (token != NULL && strtok(NULL, " \t\n") == NULL) {
        if (!isValidMacroName(token)) {
            fprintf(stderr, "Error in file %s at line %d: Invalid macro name '%s'. Macro names must start with an alphabetic character and be up to %d characters long.\n", filename, line_number, token, MAX_MACRO_NAME_LENGTH);
            *has_error = 1;
            return;
        }
        if (isReservedWord(token)) {
            fprintf(stderr, "Error in file %s at line %d: Invalid macro name '%s'. Macro names cannot be reserved words.\n", filename, line_number, token);
            *has_error = 1;
            return;
        }
        if (isMacroNameDuplicate(macros, *macro_count, token)) {
            fprintf(stderr, "Error in file %s at line %d: Duplicate macro name '%s'.\n", filename, line_number, token);
            *has_error = 1;
            return;
        }
        if (*macro_count >= *macro_capacity) {
            *macro_capacity = (*macro_capacity == 0) ? 1 : (*macro_capacity * 2);
            *macros = realloc(*macros, *macro_capacity * sizeof(Macro));
            if (*macros == NULL) {
                fprintf(stderr, "Error in file %s at line %d: Memory allocation failed.\n", filename, line_number);
                *has_error = 1;
                return;
            }
        }
        *macro_flag = 1;
        *current_macro = &(*macros)[(*macro_count)++];
        (*current_macro)->name = strdup_safe(token);
        (*current_macro)->line_count = 0;
        (*current_macro)->line_capacity = 0;
        (*current_macro)->lines = NULL;
        error_printed = 0;
    } else {
        if (!error_printed) {
            fprintf(stderr, "Error in file %s at line %d: Invalid macro start format. Correct format is 'macr macro_name'.\n", filename, line_number);
            error_printed = 1;
        }
        *has_error = 1;
    }
}

void handleMacroEnd(char *line, int *macro_flag, int *has_error, char *filename, int line_number) {
     int error_printed = 0;
    char *token = strtok(line, " \t\n");

    if (token != NULL && strcmp(token, "endmacr") == 0 && strtok(NULL, " \t\n") == NULL) {
        *macro_flag = 0;
        error_printed = 0;
    } else {
        if (!error_printed) {
            fprintf(stderr, "Error in file %s at line %d: Invalid macro end format. Correct format is 'endmacr'.\n", filename, line_number);
            error_printed = 1;
        }
        *has_error = 1;
    }
}

void handleMacroLine(char *line, Macro *current_macro) {
    if (current_macro->line_count >= current_macro->line_capacity) {
        current_macro->line_capacity = (current_macro->line_capacity == 0) ? 1 : (current_macro->line_capacity * 2);
        current_macro->lines = realloc(current_macro->lines, current_macro->line_capacity * sizeof(char *));
        if (current_macro->lines == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            exit(1);
        }
    }

    current_macro->lines[current_macro->line_count] = strdup_safe(line);
    current_macro->line_count++;
}

void handleRegularLine(char *line, FILE *output, Macro **macros, int macro_count, char *filename, int line_number) {
    char *token;
    int i, j;
    int found = 0;
    char temp_line[MAX_LINE_LENGTH];

    strcpy(temp_line, line);
    token = strtok(temp_line, " \t\n");

    if (token == NULL) {
        fprintf(output, "\n");
        return;
    }

    for (i = 0; i < macro_count; ++i) {
        if (strcmp(token, (*macros)[i].name) == 0) {
            found = 1;
            if (!isMacroNameAloneOnLine(line, (*macros)[i].name)) {
                fprintf(stderr, "Error in file %s at line %d: Macro name '%s' must be alone on its line with no other non-whitespace characters.\n", filename, line_number, (*macros)[i].name);
                return;
            }
            if (isMacroNameUsedAsLabel(line, (*macros)[i].name)) {
                fprintf(stderr, "Error in file %s at line %d: Macro name '%s' cannot be used as a label.\n", filename, line_number, (*macros)[i].name);
                return;
            }
            for (j = 0; j < (*macros)[i].line_count; ++j) {
                fprintf(output, "%s\n", (*macros)[i].lines[j]); /* Ensure each line ends correctly */
            }
            break;
        }
    }

    if (!found) {
        fprintf(output, "%s\n", line); /* Ensure each line ends correctly */
    }
}

int isValidMacroName(char *name) {
    int length = strlen(name);
    int i;
    if (length == 0 || length > MAX_MACRO_NAME_LENGTH) {
        return 0;
    }
    if (!is_letter(name[0])) {
        return 0;
    }
    for (i = 1; i < length; i++) {
        /* ASCII values */
        if (name[i] < ASCI_VALUE_33 || name[i] > ASCI_VALUE_126 || name[i] == ' ') {
            return 0;
        }
    }
    return 1;
}

int isReservedWord(char *name) {
    char *reserved_words[] = {
        "mov", "add", "sub", "lea", "jmp", "cmp", "clr", "not", "inc", "dec", "bne", "red", "prn", "jsr", "rts", "stop", ".data", ".string", ".entry", ".extern", "macr", "endmacr"};

    int reserved_word_count = sizeof(reserved_words) / sizeof(reserved_words[0]);
    int i;
    for (i = 0; i < reserved_word_count; i++) {
        if (strcmp(name, reserved_words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isMacroNameDuplicate(Macro **macros, int macro_count, char *name) {
    int i;
    for (i = 0; i < macro_count; i++) {
        if (strcmp((*macros)[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

int isMacrLineFormattedCorrectly(char *line) {
     char *start = skip_whitespace(line);
    return starts_with(start, "macr");
}
