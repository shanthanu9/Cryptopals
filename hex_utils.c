#include "hex_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Convert a hexadecimal char into byte variable.
 */
uint8_t hex_to_byte(char hex_char)
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
 * Convert a base64 char into byte variable
 */
uint8_t base64_to_byte(char base64_char)
{
    if (base64_char >= 'A' && base64_char <= 'Z')
    {
        return base64_char - 'A';
    }
    else if (base64_char >= 'a' && base64_char <= 'z')
    {
        return base64_char - 'a' + 26;
    }
    else if (base64_char >= '0' && base64_char <= '9')
    {
        return base64_char - '0' + 52;
    }
    else if (base64_char == '+')
    {
        return 62;
    }
    else if (base64_char == '/')
    {
        return 63;
    }
    else if (base64_char == '=')
    {
        // Should be ok to return 64 on padding character?
        return 64;
    }
    else
    {
        printf("[ERROR] Not a valid base64 character: %c", base64_char);
        exit(1);
    }
}

/*
 * Convert hex string to bytes.
 * The user is responsible for freeing up the memory of bytes allocated.
 */
uint8_t *hex_str_to_bytes(char *hex_str, int hex_length)
{
    const int byte_length = hex_length / 2;

    uint8_t *bytes = (uint8_t *)malloc(byte_length);

    if (bytes == NULL)
    {
        printf("%s: Error in allocating memory for `bytes`", __func__);
        exit(1);
    }

    for (int i = 0; i < byte_length; i++)
    {
        bytes[i] = (hex_to_byte(hex_str[2 * i]) << 4) + hex_to_byte(hex_str[2 * i + 1]);
    }

    return bytes;
}

int get_byte_length_of_base64_str(char *base64_str, int base64_length)
{
    int byte_length = (base64_length / 4) * 3;

    // Check of padding character '='
    if (base64_str[base64_length - 1] == '=' && base64_str[base64_length - 2] == '=')
    {
        byte_length -= 2;
    }
    else if (base64_str[base64_length - 1] == '=')
    {
        byte_length--;
    }

    return byte_length;
}

/*
 * Convert base64 string to bytes.
 * The user is responsible for freeing up the memory of bytes allocated.
 */
uint8_t *base64_str_to_bytes(char *base64_str, int base64_length)
{
    int byte_length = get_byte_length_of_base64_str(base64_str, base64_length);

    uint8_t *bytes = (uint8_t *)malloc(byte_length);

    if (bytes == NULL)
    {
        printf("%s: Error in allocating memory for `bytes`", __func__);
        exit(1);
    }

    for (int i = 0; i < byte_length / 3; i++)
    {
        const uint8_t a = base64_to_byte(base64_str[4 * i]);
        const uint8_t b = base64_to_byte(base64_str[4 * i + 1]);
        const uint8_t c = base64_to_byte(base64_str[4 * i + 2]);
        const uint8_t d = base64_to_byte(base64_str[4 * i + 3]);

        bytes[3 * i] = (a << 2) | (b >> 4);
        bytes[3 * i + 1] = (b << 4) | (c >> 2);
        bytes[3 * i + 2] = (c << 6) | d;
    }

    // Handle padding
    if (byte_length % 3 != 0)
    {
        int i = byte_length / 3;
        const uint8_t a = base64_to_byte(base64_str[4 * i]);
        const uint8_t b = base64_to_byte(base64_str[4 * i + 1]);
        const uint8_t c = base64_to_byte(base64_str[4 * i + 2]);

        // We know byte_length % 3 is 1 or 2
        bytes[3 * i] = (a << 2) | (b >> 4);
        if (byte_length % 3 == 2)
        {
            bytes[3 * i + 1] = (b << 4) | (c >> 2);
        }
    }

    return bytes;
}

/*
 * Compute fixed xor of 2 byte strings
 */
uint8_t *fixed_xor(uint8_t *bytes1, uint8_t *bytes2, int byte_length)
{
    uint8_t *out_bytes = (uint8_t *)malloc(byte_length);

    if (out_bytes == NULL)
    {
        printf("%s: Error in allocating memory for `out_bytes`", __func__);
        exit(1);
    }

    for (int i = 0; i < byte_length; i++)
    {
        out_bytes[i] = bytes1[i] ^ bytes2[i];
    }
    return out_bytes;
}

/*
 * Compute repeat key xor of bytes with key
 */
uint8_t *repeating_key_xor(uint8_t *bytes, uint8_t *key,
                           int byte_length, int key_length, int key_start_point)
{
    uint8_t *out_bytes = (uint8_t *)malloc(byte_length);

    if (out_bytes == NULL)
    {
        printf("%s: Error in allocating memory for `out_bytes`", __func__);
        exit(1);
    }

    for (int i = 0; i < byte_length; i++)
    {
        out_bytes[i] = bytes[i] ^ key[(key_start_point + i) % key_length];
    }
    return out_bytes;
}

/*
 * Pretty print bytes in hexadecimal.
 */
void pretty_print_bytes_in_hex(uint8_t *bytes, int byte_length)
{
    for (int i = 0; i < byte_length; i++)
    {
        printf("%02x", bytes[i]);
    }
    printf("\n");
}