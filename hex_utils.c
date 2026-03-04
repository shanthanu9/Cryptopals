#include "hex_utils.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Convert a hexadecimal number (given in char datatype) into decimal variable.
 */
unsigned char hex_to_decimal(char hex_char)
{
    switch (hex_char)
    {
    case '0':
        return 0;
        break;
    case '1':
        return 1;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7':
        return 7;
        break;
    case '8':
        return 8;
        break;
    case '9':
        return 9;
        break;
    case 'a':
    case 'A':
        return 10;
        break;
    case 'b':
    case 'B':
        return 11;
        break;
    case 'c':
    case 'C':
        return 12;
        break;
    case 'd':
    case 'D':
        return 13;
        break;
    case 'e':
    case 'E':
        return 14;
        break;
    case 'f':
    case 'F':
        return 15;
        break;
        ;
    default:
        printf("[ERROR] Not a valid hexadecimal character: %c", hex_char);
        exit(1);
    }
}

/*
 * Convert hex string to bytes.
 * The user is responsible for freeing up the memory of bytes allocated.
 */
unsigned char *hex_str_to_bytes(char *hex_str, int hex_length)
{
    const int byte_length = hex_length / 2;

    unsigned char *bytes = (unsigned char *)malloc(byte_length);
    for (int i = 0; i < byte_length; i++)
    {
        bytes[i] = (hex_to_decimal(hex_str[2 * i]) << 4) + hex_to_decimal(hex_str[2 * i + 1]);
    }

    return bytes;
}

/*
 * Pretty print bytes in hexadecimal.
 */
void pretty_print_bytes_in_hex(unsigned char *bytes, int byte_length)
{
    for (int i = 0; i < byte_length; i++)
    {
        printf("%x", bytes[i]);
    }
    printf("\n");
}