#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_utils.h"

int main()
{
    // Input
    char hex_str[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    const int hex_length = strlen(hex_str);
    const int byte_length = hex_length / 2;

    unsigned char *bytes = hex_str_to_bytes(hex_str, hex_length);

    for (int i = 0; i < 256; i++)
    {
        unsigned char *candidate_bytes_key = (unsigned char *)malloc(byte_length);

        for (int j = 0; j < byte_length; j++)
        {
            candidate_bytes_key[j] = (unsigned char)i;
        }

        unsigned char *candidate_bytes_msg = fixed_xor(bytes, candidate_bytes_key, byte_length);

        // sanity check for messages with printable characters
        // filter out messages with too few alphabets/numbers
        int all_printable_characters = 1;
        int count_of_english_like_characters = 0;
        for (int j = 0; j < byte_length; j++)
        {
            if (!(candidate_bytes_msg[j] >= 32 && candidate_bytes_msg[j] <= 126))
            {
                all_printable_characters = 0;
                break;
            }
            if ((candidate_bytes_msg[j] >= 'a' && candidate_bytes_msg[j] <= 'z') ||
                (candidate_bytes_msg[j] >= 'A' && candidate_bytes_msg[j] <= 'Z') ||
                (candidate_bytes_msg[j] >= '0' && candidate_bytes_msg[j] <= '9') ||
                candidate_bytes_msg[j] == ' ' || candidate_bytes_msg[j] == '.')
            {
                count_of_english_like_characters++;
            }
        }

        // Very rudimentry way to filter out strings looking like english
        // If it's english, then there should be lot of letters, numbers, spaces and all
        if (all_printable_characters && count_of_english_like_characters >= byte_length - 3)
        {
            printf("%s\n", candidate_bytes_msg);
        }

        free(candidate_bytes_key);
        free(candidate_bytes_msg);
    }

    free(bytes);
}