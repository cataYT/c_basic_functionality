#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * Reads a string input from stdin into a caller-provided buffer.
 * 
 * @param msg        The prompt message to display (cannot be NULL).
 * @param out        Buffer to store the result (must be at least `max_length + 1` bytes).
 * @param max_length Maximum length of input (excluding null terminator).
 * @return           true on success, false on error.
 */
bool get_string_input(const char *msg, char *out, const size_t length);
/**
 * Reads an integer input from stdin.
 * 
 * @param msg    The prompt message to display (cannot be NULL).
 * @param out    Pointer to store the integer result (cannot be NULL).
 * @return       true on success, false on error.
 */
bool get_int_input(const char *msg, int *out);