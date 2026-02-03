#ifndef MULTIPLE_USE_H
#define MULTIPLE_USE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define R0 "r0"
#define R1 "r1"
#define R2 "r2"
#define R3 "r3"
#define R4 "r4"
#define R5 "r5"
#define R6 "r6"
#define R7 "r7"


#define ASCI_VALUE_33  33
#define ASCI_VALUE_126  126

/* general functions */

/* Check if a character is a letter */
int is_letter(char c);

/* Skip leading whitespace in a string */
 char *skip_whitespace( char *str);

/* Check if a string starts with a given keyword */
int starts_with( char *str,  char *keyword);

/* Duplicate a string */
char *strdup_safe( char *s);

/* Open a file and check for errors */
FILE *open_file( char *filename,  char *mode);

/* Function to check if the first non-whitespace character is a letter or a dot */
int check_first_char(char *line);

/* Function to check if the first word is immediately followed by a colon */
int check_word_colon(char *line);

/* checks #num*/
int check_hash_no_whitespace(char *line);

/* checks *rnum */
int check_star_not_followed_by_register(char *line);

/* check if a word is a reserved word */
int is_reserved_word(char *word);

/* check if a word is a valid register */
int is_valid_register(char *word);

/* check if the first character of a line is a special character ( whitespace, \n) */
int is_first_char_special(char *line);

#endif /* MULTIPLE_USE_H */
