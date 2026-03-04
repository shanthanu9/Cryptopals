#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hex_utils.h"

int main()
{
    // Input
    char hex_str1[] = "1c0111001f010100061a024b53535009181c";
    char hex_str2[] = "686974207468652062756c6c277320657965";
    const int hex_length = strlen(hex_str1);
    const int byte_length = hex_length / 2;

    // Convert hex str to bytes
    unsigned char *bytes1 = hex_str_to_bytes(hex_str1, hex_length);
    unsigned char *bytes2 = hex_str_to_bytes(hex_str2, hex_length);

    // Compute Fixed XOR
    unsigned char *out_bytes = fixed_xor(bytes1, bytes2, byte_length);

    // Output
    pretty_print_bytes_in_hex(out_bytes, byte_length);

    // Free up memory
    free(out_bytes);
    free(bytes1);
    free(bytes2);

}