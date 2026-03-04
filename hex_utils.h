#ifndef HEX_UTILS_H
#define HEX_UTILS_H

unsigned char hex_to_decimal(char hex_char);
unsigned char *hex_str_to_bytes(char *hex_str, int hex_length);
unsigned char *fixed_xor(unsigned char *bytes1, unsigned char *bytes2, int byte_length);
unsigned char *repeating_key_xor(unsigned char *bytes, unsigned char *key,
                                 int byte_length, int key_length, int key_start_point);
void pretty_print_bytes_in_hex(unsigned char *bytes, int byte_length);

#endif