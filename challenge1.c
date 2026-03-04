#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Convert a hexadecimal number (given in char datatype) into decimal variable.
 */
unsigned short hex_to_decimal(char hex_char)
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

int main()
{
    char hex_str[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    const int hex_length = strlen(hex_str);
    const int bit_length = hex_length * 4;
    const int byte_length = bit_length / 8;
    const int base64_length = bit_length / 6;

    // First convert hex char string to bytes
    unsigned char *bytes = (unsigned char *)malloc(byte_length);
    for (int i = 0; i < byte_length; i++)
    {
        bytes[i] = (hex_to_decimal(hex_str[2 * i]) << 4) + hex_to_decimal(hex_str[2 * i + 1]);
    }

    // for (int i = 0; i < byte_length; i++)
    // {
    //     for (int j = 7; j >= 0; j--)
    //     {
    //         if (((1 << j) & bytes[i]) != 0) printf("1");
    //         else printf("0");
    //         // printf("%d", !!((1 << j) | bytes[i]));
    //     }
    //     printf(" ");
    // }
    // printf("\n");


    // Convert to base64
    char *base64_str = (char *)malloc(base64_length);

    for (int i = 0; i < byte_length / 3; i++)
    {
        unsigned char x = bytes[3 * i];
        unsigned char y = bytes[3 * i + 1];
        unsigned char z = bytes[3 * i + 2];

        base64_str[4 * i] = decimal_to_base64_char(x >> 2);
        base64_str[4 * i + 1] = decimal_to_base64_char(((x & 3) << 4) + (y >> 4));
        base64_str[4 * i + 2] = decimal_to_base64_char(((y & 15) << 2) + (z >> 6));
        base64_str[4 * i + 3] = decimal_to_base64_char(z & 63);

        // base64_str[4 * i] = x >> 2;
        // base64_str[4 * i + 1] = ((x & 3) << 4) + (y >> 4);
        // base64_str[4 * i + 2] = ((y & 15) << 2) + (z >> 6);
        // base64_str[4 * i + 3] = z & 63;

        // printf("%c\n", base64_str[4 * i]);
        // printf("%c\n", base64_str[4 * i+1]);
        // printf("%c\n", base64_str[4 * i+2]);
        // printf("%c\n", base64_str[4 * i+3]);
    }

    printf("%s\n", base64_str);

    free(base64_str);
    free(bytes);
}