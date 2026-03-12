#ifndef HEX_UTILS_H
#define HEX_UTILS_H

#include <stdint.h>

uint8_t hex_to_byte(char hex_char);
uint8_t base64_to_byte(char base64_char);
uint8_t *hex_str_to_bytes(char *hex_str, int hex_length);
int get_byte_length_of_base64_str(char *base64_str, int base64_length);
uint8_t *base64_str_to_bytes(char *base64_str, int base64_length);
uint8_t *fixed_xor(uint8_t *bytes1, uint8_t *bytes2, int byte_length);
uint8_t *repeating_key_xor(uint8_t *bytes, uint8_t *key,
                           int byte_length, int key_length, int key_start_point);
void pretty_print_bytes_in_hex(uint8_t *bytes, int byte_length);

#endif