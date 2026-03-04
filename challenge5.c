#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_utils.h"

int count_letter_frequency(unsigned char *str, int str_len);

int main()
{
    // Input from file
    const char INPUT_FILE_NAME[] = "5.txt";
    unsigned char REPEAT_KEY[] = "ICE";
    const int REPEAT_KEY_LENGTH = 3;
    FILE *fp = fopen(INPUT_FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("[ERROR] Error opening file %s\n", INPUT_FILE_NAME);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char *buffer = malloc(file_size + 1);
    if (!buffer)
    {
        printf("[ERROR] Error allocating space for reading file\n");
        fclose(fp);
        return 1;
    }

    fread(buffer, 1, file_size, fp);
    buffer[file_size] = '\0';

    unsigned char *bytes = buffer;
    const int byte_length = strlen(bytes);

    unsigned char *out_bytes = repeating_key_xor(bytes, REPEAT_KEY,
                                                 byte_length, REPEAT_KEY_LENGTH, 0);
    pretty_print_bytes_in_hex(out_bytes, byte_length);
    
    free(out_bytes);
    fclose(fp);
}

