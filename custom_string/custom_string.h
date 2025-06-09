#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct string
 * @brief A dynamic string structure for safe and flexible string manipulation.
 *
 * Manages memory allocation, resizing, and string operations using a custom
 * string structure to avoid buffer overflows and support advanced string ops.
 */
struct string {
    char *str;           /**< Pointer to the null-terminated character array */
    size_t size;         /**< Current length of the string (excluding null terminator) */
    size_t capacity;     /**< Allocated memory capacity for the string (including space for null terminator) */
};

/**
 * @brief Initializes a new dynamic string.
 *
 * Copies a C-string into a managed `string` struct with allocated memory.
 *
 * @param string Input C-string to initialize from.
 * @param capacity Total allocated capacity (must be >= strlen(string) + 1).
 * @param str Pointer to the string structure to initialize.
 * @return true if successful, false on memory failure or invalid input.
 */
bool create_string(const char *string, const size_t capacity, struct string *str);

/**
 * @brief Updates the content and capacity of an existing string.
 *
 * Replaces the old string data with a new one, resizing the buffer.
 *
 * @param old_string Pointer to the existing string to modify.
 * @param new_capacity New capacity to allocate.
 * @param new_string New string data to copy in.
 * @return true if successful, false otherwise.
 */
bool update_string(struct string *old_string, const size_t new_capacity, const char *new_string);

/**
 * @brief Prints the string as space-separated tokens.
 *
 * Tokenizes the string using whitespace and prints each token on a new line.
 *
 * @param strr Pointer to the string to tokenize and print.
 */
void print_tokens(const struct string *strr);

/**
 * @brief Prints the string to standard output.
 *
 * @param strr Pointer to the string to print.
 */
void print_string(const struct string *strr);

/**
 * @brief Compares two strings for equality.
 *
 * @param strr1 Pointer to the first string.
 * @param strr2 Pointer to the second string.
 * @return true if both strings are equal in content and length, false otherwise.
 */
bool compare_string(const struct string *strr1, const struct string *strr2);

/**
 * @brief Concatenates two strings and stores the result in a third string.
 *
 * The output string must be preallocated with enough capacity.
 *
 * @param strr1 Pointer to the first string.
 * @param strr2 Pointer to the second string.
 * @param capacity Capacity of the output string buffer.
 * @param out_string Pointer to the result string structure.
 * @return true if concatenation succeeded, false on capacity/memory failure.
 */
bool add_string(const struct string *strr1, const struct string *strr2, const size_t capacity, struct string *out_string);

/**
 * @brief Extracts a substring from a string.
 *
 * Copies a range of characters into a new string structure.
 *
 * @param strr Pointer to the source string.
 * @param start Starting index of the substring (0-based).
 * @param length Number of characters to extract.
 * @param substring Pointer to the destination string structure.
 * @return true if the substring was successfully extracted, false if out of bounds.
 */
bool substring(const struct string *strr, const size_t start, const size_t length, struct string *substring);

/**
 * @brief Frees the memory allocated by a string.
 *
 * Releases the string buffer and resets fields to zero/null.
 *
 * @param strr Pointer to the string structure to free.
 * @return true if memory was successfully freed, false otherwise.
 */
bool free_string(struct string *strr);