#ifndef FILE_READER_H
#define FILE_READER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiple_use.h"



#define MAX_LINE_LENGTH 81
#define MAX_MACRO_NAME_LENGTH 31
#define MEMORY_SIZE 4096  /* total memory size */
#define CHUNK_SIZE 64     /* initial chunk size for each allocation */
#define INITIAL_BUFFER_SIZE 1024  /*Initial buffer size for line reading*/

/* struct for representing a macro with its name and associated lines */
typedef struct {
    char *name;
    char **lines; /* array of lines in the macro */
    int line_count;
    int line_capacity; /* num of chars in line */
} Macro;

/* 
 * replaces the file extension of the given filename with a new extension.
 * this function modifies the input filename directly to change its extension.
 */
void replaceFileExtension(char *filename, char *new_extension);

/* 
 * processes a list of assembly source files to expand macros and write the expanded code to new files.
 * it handles multiple files by iterating over each, processing macros, and generating output files with expanded content.
 */
void readAndPrintFiles(char **filenames, int file_count);

/* 
 * processes a single file to detect and handle macro definitions and usages.
 * it reads the file line-by-line, identifies macro definitions, validates their correctness,
 * and writes the expanded code to the output file.
 *
 * returns:
 * - an integer indicating if any errors were encountered (0 for success, non-zero for failure).
 */
int processFile(FILE *file, FILE *output, Macro **macros, int *macro_count, int *macro_capacity, char *filename);

#endif /* FILE_READER_H */
