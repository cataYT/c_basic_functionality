#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * Reads a string input from stdin into a caller-provided buffer.
 * 
 * @param[in]  msg        The prompt message to display (cannot be NULL).
 * @param[in]  max_length Maximum length of input (excluding null terminator).
 * @param[out] out        Buffer to store the result (must be at least `max_length + 1` bytes).
 * 
 * @return true on success, false on error.
 */
bool get_string_input(const char *msg, const size_t length, char *out);
/**
 * Converts a string to unsigned long.
 * 
 * @param[in]  str String to convert.
 * @param[out] out Pointer to store the unsigned long result (cannot be NULL).
 * 
 * @return true on success, false on error.
 */
bool parse_unsigned_long(const char *str, unsigned long *out);