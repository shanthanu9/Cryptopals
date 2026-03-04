#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hex_utils.h"

char decimal_to_base64_char(unsigned char base64_val);

int main()
{
    // Input hex string
    char hex_str[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    const int hex_length = strlen(hex_str);
    const int bit_length = hex_length * 4;
    const int byte_length = bit_length / 8;
    const int base64_length = bit_length / 6;

    // First convert hex char string to bytes
    unsigned char *bytes = hex_str_to_bytes(hex_str, hex_length);

    // Convert to base64
    char *base64_str = (char *)malloc(base64_length);

    // We iterate over 3 bytes at a time
    // We convert 3 bytes (24 bits) into 4 base64 numbers
    for (int i = 0; i < byte_length / 3; i++)
    {
        unsigned char x = bytes[3 * i];
        unsigned char y = bytes[3 * i + 1];
        unsigned char z = bytes[3 * i + 2];

        base64_str[4 * i] = decimal_to_base64_char(x >> 2);
        base64_str[4 * i + 1] = decimal_to_base64_char(((x & 3) << 4) + (y >> 4));
        base64_str[4 * i + 2] = decimal_to_base64_char(((y & 15) << 2) + (z >> 6));
        base64_str[4 * i + 3] = decimal_to_base64_char(z & 63);
    }

    printf("%s\n", base64_str);

    free(base64_str);
    free(bytes);
}

/*
 * Convert decimal to base64 char
 */
char decimal_to_base64_char(unsigned char base64_val)
{
    if (base64_val >= 0 && base64_val <= 25)
    {
        return 'A' + base64_val;
    }
    else if (base64_val >= 26 && base64_val <= 51)
    {
        return 'a' + (base64_val - 26);
    }
    else if (base64_val >= 52 && base64_val <= 61)
    {
        return '0' + (base64_val - 52);
    }
    else if (base64_val == 62)
    {
        return '+';
    }
    else if (base64_val == 63)
    {
        return '/';
    }
    else
    {
        printf("[ERROR] Base 64 value is invalid: %d", base64_val);
        exit(1);
    }
}