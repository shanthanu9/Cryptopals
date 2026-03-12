#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hex_utils.h"

int main()
{
    char base64_str[] = "HUIfTQsP";
    const int BASE64_STR_LEN = strlen(base64_str);
    const int BYTES_LEN = (BASE64_STR_LEN / 4) * 3;

    uint8_t *bytes = base64_str_to_bytes(base64_str, BASE64_STR_LEN);
    // printf("%d\n", bytes[1]);

    pretty_print_bytes_in_hex(bytes, BYTES_LEN);

    free(bytes);
}