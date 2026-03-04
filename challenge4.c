#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_utils.h"

int count_letter_frequency(unsigned char *str, int str_len);

int main()
{
    // Input from file
    const char INPUT_FILE_NAME[] = "4.txt";
    const int INPUT_FILE_LINE_LENGTH = 62; // each line has 60 characters + newline + '\0' null termination
    FILE *fp = fopen(INPUT_FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("[ERROR] Error opening file %s\n", INPUT_FILE_NAME);
    }

    char line[INPUT_FILE_LINE_LENGTH];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Have to discard the final "\n" character
        line[INPUT_FILE_LINE_LENGTH] = '\0';
        char *hex_str = line;
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

            int score = count_letter_frequency(candidate_bytes_msg, byte_length);

            if (score >= 17)
            {
                printf("%s\n", candidate_bytes_msg);
            }

            free(candidate_bytes_key);
            free(candidate_bytes_msg);
        }

        free(bytes);
    }

    fclose(fp);
}

int count_letter_frequency(unsigned char *str, int str_len)
{
    unsigned int letter_frequency_count[256] = {0};
    for (int i = 0; i < str_len; i++)
    {
        letter_frequency_count[str[i]]++;
    }

    int score = letter_frequency_count['e'] + letter_frequency_count['t'] +
                letter_frequency_count['a'] + letter_frequency_count['o'] +
                letter_frequency_count['i'] + letter_frequency_count['n'] +
                letter_frequency_count['s'] + letter_frequency_count['h'] +
                letter_frequency_count['r'] + letter_frequency_count['d'] +
                letter_frequency_count['l'] + letter_frequency_count['u'] +
                letter_frequency_count['E'] + letter_frequency_count['T'] +
                letter_frequency_count['A'] + letter_frequency_count['O'] +
                letter_frequency_count['I'] + letter_frequency_count['N'] +
                letter_frequency_count['S'] + letter_frequency_count['H'] +
                letter_frequency_count['R'] + letter_frequency_count['D'] +
                letter_frequency_count['L'] + letter_frequency_count['U'];

    return score;
}