#include "byte_buffer.h"
#include "hex_utils.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

ByteBuffer *create_byte_buffer(size_t buffer_len)
{
    ByteBuffer *buffer = malloc(sizeof(ByteBuffer));

    if (buffer == NULL)
    {
        printf("%s: Error in allocating memory for `buffer`", __func__);
        exit(1);
    }

    buffer->data = malloc(buffer_len * sizeof(uint8_t));

    if (buffer->data == NULL)
    {
        free(buffer);
        printf("%s: Error in allocating memory for `buffer->data`", __func__);
        exit(1);
    }

    buffer->length = buffer_len;
    return buffer;
}

/*
 * Convert base64 string to bytes.
 * The user is responsible for freeing up the memory of bytes allocated.
 */
ByteBuffer *create_byte_buffer_from_base64_str(char *base64_str, int base64_length)
{
    ByteBuffer *buffer = malloc(sizeof(ByteBuffer));

    if (buffer == NULL)
    {
        printf("%s: Error in allocating memory for `buffer`", __func__);
        exit(1);
    }

    buffer->length = get_byte_length_of_base64_str(base64_str, base64_length);
    buffer->data = base64_str_to_bytes(base64_str, base64_length);
    return buffer;
}

ByteBuffer *create_byte_buffer_from_hex_str(char* hex_str, int hex_length)
{
    ByteBuffer *buffer = malloc(sizeof(ByteBuffer));

    if (buffer == NULL)
    {
        printf("%s: Error in allocating memory for `buffer`", __func__);
        exit(1);
    }

    buffer->length = hex_length / 2;
    buffer->data = hex_str_to_bytes(hex_str, hex_length);
    return buffer;
}

void free_byte_buffer(ByteBuffer *buffer)
{
    if (buffer == NULL)
    {
        return;
    }

    free(buffer->data);
    free(buffer);
}

void pretty_print_byte_buffer(ByteBuffer *buffer)
{
    pretty_print_bytes_in_hex(buffer->data, buffer->length);
}