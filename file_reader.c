#include "file_reader.h"
#include "macro_handler.h"
#include "am_check.h"


/* Replace the file extension with a new extension */
void replaceFileExtension(char *filename, char *new_extension) {
    char *dot = strrchr(filename, '.');
    if (dot != NULL) {
        *dot = '\0'; /* Remove the current extension */
    }
    strncat(filename, new_extension, MAX_LINE_LENGTH - strlen(filename) - 1);
}

/* Read and process each file in the list of filenames */
void readAndPrintFiles(char **filenames, int file_count) {
    Macro *macros = NULL;
    int macro_count = 0;
    int macro_capacity = 0;
    int i;
    int j;
    char output_filename[MAX_LINE_LENGTH];
    FILE *file;
    FILE *output;
    int has_error;

    for (i = 0; i < file_count; ++i) {
        printf("Reading file: %s\n", filenames[i]);
        file = open_file(filenames[i], "r");

        strncpy(output_filename, filenames[i], MAX_LINE_LENGTH - 1);
        output_filename[MAX_LINE_LENGTH - 1] = '\0'; /* Ensure null termination */
        replaceFileExtension(output_filename, ".am");

        output = open_file(output_filename, "w");

        macros = NULL;
        macro_count = 0;
        macro_capacity = 0;

        has_error = processFile(file, output, &macros, &macro_count, &macro_capacity, filenames[i]);

        fclose(file);
        fclose(output);

        if (has_error) {
            remove(output_filename);
        } else {
            /* Read the .am file to perform checks and processing */
            readAmFile(output_filename);
        }
    }

    /* Free allocated memory for macros */
    for (i = 0; i < macro_count; ++i) {
        free(macros[i].name);
        for (j = 0; j < macros[i].line_count; ++j) {
            free(macros[i].lines[j]);
        }
        free(macros[i].lines);
    }
    free(macros);
}

/* Process a single file and handle macros */

int processFile(FILE *file, FILE *output, Macro **macros, int *macro_count, int *macro_capacity, char *filename) {
    char *line = NULL;
 	char *new_line = NULL;
    int buffer_size = INITIAL_BUFFER_SIZE;
    int line_number = 0;
    int has_error = 0;
    int macro_flag = 0;
    Macro *current_macro = NULL;
    char *comment_start;

    /*Allocate initial memory for line*/
    line = (char *)malloc(buffer_size * sizeof(char));
    if (line == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;  /* Return failure*/
    }

    /* Read file line by line without a fixed line limit*/
    while (fgets(line, buffer_size, file) != NULL) {
        size_t len = strlen(line);
        line_number++;

        /* Check if the line ends with a newline character or EOF*/
        while (len > 0 && line[len - 1] != '\n' && !feof(file)) {
            /*Line is longer than the current buffer size, need to reallocate*/
            buffer_size *= 2;
            new_line = realloc(line, buffer_size * sizeof(char));
            if (new_line == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(line);
                return 1;  /* Return failure*/
            }
            line = new_line;

            /* Read the rest of the line*/
            if (fgets(line + len, buffer_size - len, file) == NULL) {
                break;
            }

            len = strlen(line);
        }

        /* Trim newline character if present*/
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        /* Check for long line error*/
        if (len > 80) {
            fprintf(output, "%s\n", line);
            continue; /* Continue to the next line */
        }   

        /* Remove comments from the line*/
        comment_start = strchr(line, ';');
        if (comment_start != NULL) {
            if (comment_start != line) {
                fprintf(stderr, "Error in file %s at line %d: Comments must start on a new line without any leading whitespace or characters.\n", filename, line_number);
                has_error = 1;
            }
            *comment_start = '\0'; /*Remove the comment part*/
        }

        /*Process macros*/
        if (macro_flag) {
            if (strstr(line, "endmacr")) {
                handleMacroEnd(line, &macro_flag, &has_error, filename, line_number);
            } else {
                handleMacroLine(line, current_macro);
            }
        } else {
            if (strstr(line, "macr")) {
                if (strstr(line, "endmacr")) {
                    handleRegularLine(line, output, macros, *macro_count, filename, line_number);
                } else {
                    handleMacroStart(line, macros, macro_count, macro_capacity, &macro_flag, &current_macro, &has_error, filename, line_number);
                }
            } else {
                handleRegularLine(line, output, macros, *macro_count, filename, line_number);
            }
        }
    }

    /* Free allocated memory for line*/
    free(line);

    return has_error;
}
