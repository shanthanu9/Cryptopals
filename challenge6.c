#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hex_utils.h"
#include "byte_buffer.h"

int main()
{
    /***** READ INPUT FILE *****/
    const char INPUT_FILE_NAME[] = "6.txt";
    const int INPUT_FILE_NUMBER_OF_CHARS_PER_LINE = 60; // not including newline
    const int INPUT_FILE_LINE_LENGTH = 62;              // each line has 60 characters + newline + '\0' null termination
    const int INPUT_FILE_SIZE = 60 * 64 + 1;            // Based on number of lines and characters per lin
    FILE *fp = fopen(INPUT_FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("[ERROR] Error opening file %s\n", INPUT_FILE_NAME);
    }

    char line[INPUT_FILE_LINE_LENGTH];
    uint8_t content[INPUT_FILE_SIZE];
    int current_read_pointer = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Copy by hand because I trust myself more than strcpy function
        for (int i = 0; i < INPUT_FILE_NUMBER_OF_CHARS_PER_LINE; i++)
        {
            // Break when we encounter newline or null
            if (line[i] == '\n' || line[i] == '\0')
            {
                break;
            }
            content[current_read_pointer] = line[i];
            current_read_pointer++;
        }
    }
    content[current_read_pointer] = '\0';

    
    ByteBuffer *buffer = create_byte_buffer_from_base64_str(content, current_read_pointer);

    free_byte_buffer(buffer);
}