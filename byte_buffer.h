#ifndef BYTE_BUFFER_H
#define BYTE_BUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint8_t *data;
    size_t length;
} ByteBuffer;

ByteBuffer *create_byte_buffer(size_t buffer_len);
ByteBuffer *create_byte_buffer_from_base64_str(char *base64_str, int base64_length);
void free_byte_buffer(ByteBuffer *buffer);
void pretty_print_byte_buffer(ByteBuffer *buffer);

#endif