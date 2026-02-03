#include "creating_product_files.h"


void print_15bit_octal(FILE *file, unsigned short num) {
    int i;
    unsigned short octal_digit;
    unsigned short represent = 0x7; 
    char octal_string[6] = "00000";
    
    /* start from the 12th bit (the highest multiple of 3 below 15) and move downwards */
    for (i = 12; i >= 0; i -= 3) {
        octal_digit = (num >> i) & represent; /* extract the current 3bits */
        octal_string[4 - i / 3] = '0' + octal_digit; /* convert to ASCII and store in string */
    }

    
    fprintf(file, "%s\n", octal_string);
}



void creating_output_files( char *filename, EncodingTable *encoding_head, DataTable *data_head, 
                           entry_for_output *entry_head, extern_for_output *extern_head) {
    FILE *ob_file, *ent_file, *ext_file;
    int dc = 100, encoding_count = 0, data_count = 0;
    char *ob_filename, *ent_filename, *ext_filename;
    char *base_filename;
    EncodingTable *encoding_curr;
    DataTable *data_curr;
    entry_for_output *entry_curr;
    extern_for_output *extern_curr;

    
    base_filename = (char *)malloc(strlen(filename) + 1);
    if (base_filename == NULL) {
        fprintf(stderr, "Memory allocation failed for base_filename\n");
        return;
    }
    strcpy(base_filename, filename);

    /* replace the extension with .ob */
    ob_filename = (char *)malloc(strlen(base_filename) + 4);
    if (ob_filename == NULL) {
        fprintf(stderr, "Memory allocation failed for ob_filename\n");
        free(base_filename);
        return;
    }
    strcpy(ob_filename, base_filename);
    replaceFileExtension(ob_filename, ".ob");

    /* count the number of elements in encodingTable and DataTable */
    encoding_curr = encoding_head;
    while (encoding_curr != NULL) {
        encoding_count++;
        encoding_curr = encoding_curr->next;
    }

    data_curr = data_head;
    while (data_curr != NULL) {
        data_count++;
        data_curr = data_curr->next;
    }

    /* create .ob file */
    ob_file = fopen(ob_filename, "w");
    if (ob_file == NULL) {
        fprintf(stderr, "Error creating file: %s\n", ob_filename);
        free(ob_filename);
        free(base_filename);
        return;
    }

/* check if at least one of encoding_count or data_count is not zero */
    if (encoding_count > 0 || data_count > 0) {
        /* Write the first line with the counts */
        fprintf(ob_file, "\t  %d %d\n", encoding_count, data_count);
    } else {
       
        fclose(ob_file);
        remove(ob_filename);
    }

    /* write the EncodingTable */
    dc = 100;  
    encoding_curr = encoding_head;
    while (encoding_curr != NULL) {
        /* print the machine code in 5-digit octal format */
        fprintf(ob_file, "\t%04d ", dc++);
        print_15bit_octal(ob_file,encoding_curr->machine_code);
        encoding_curr = encoding_curr->next;
    }

    /* write the DataTable */
    data_curr = data_head;
    while (data_curr != NULL) {
       
        fprintf(ob_file, "\t%04d ", dc++);
        print_15bit_octal(ob_file,data_curr->machine_code);
        data_curr = data_curr->next;
    }

    fclose(ob_file);  
    free(ob_filename);  

    /* if entry_for_output list is not empty, create .ent file */
    if (entry_head != NULL) {
        ent_filename = (char *)malloc(strlen(base_filename) + 5);
        if (ent_filename == NULL) {
            fprintf(stderr, "Memory allocation failed for ent_filename\n");
            free(base_filename);
            return;
        }
        strcpy(ent_filename, base_filename);
        replaceFileExtension(ent_filename, ".ent");

        ent_file = fopen(ent_filename, "w");
        if (ent_file == NULL) {
            fprintf(stderr, "Error creating file: %s\n", ent_filename);
            free(ent_filename);
            free(base_filename);
            return;
        }

        /* write each entry in a new line with its position */
        entry_curr = entry_head;
        while (entry_curr != NULL) {
            fprintf(ent_file, "\t%s %d\n", entry_curr->name, entry_curr->position);
            entry_curr = entry_curr->next;
        }

        fclose(ent_file);  /* close the .ent file */
        free(ent_filename); 
    }

    /* if extern_for_output list is not empty, create .ext file */
    if (extern_head != NULL) {
        ext_filename = (char *)malloc(strlen(base_filename) + 5); /* 5 for ".ext" and null terminator */
        if (ext_filename == NULL) {
            fprintf(stderr, "Memory allocation failed for ext_filename\n");
            free(base_filename);
            return;
        }
        strcpy(ext_filename, base_filename);
        replaceFileExtension(ext_filename, ".ext");

        ext_file = fopen(ext_filename, "w");
        if (ext_file == NULL) {
            fprintf(stderr, "Error creating file: %s\n", ext_filename);
            free(ext_filename);
            free(base_filename);
            return;
        }

        
        extern_curr = extern_head;
        while (extern_curr != NULL) {
            fprintf(ext_file, "\t%s %d\n", extern_curr->name, extern_curr->position);
            extern_curr = extern_curr->next;
        }

        fclose(ext_file);  
        free(ext_filename);  
    }

    
    free(base_filename);
}


