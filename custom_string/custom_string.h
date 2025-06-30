#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct string
 * @brief  A dynamic string structure for safe and flexible string manipulation.
 *
 * Manages memory allocation, resizing, and string operations using a custom
 * string structure to avoid buffer overflows and support advanced string ops.
 */
struct string {
    /** Pointer to the null-terminated character array */
    char *str;
    /** Current length of the string (excluding null terminator) */
    size_t size;
    /** Allocated memory capacity for the string (including space for null terminator) */
    size_t capacity;
};

/**
 * @brief Initializes a new dynamic string.
 *
 * Copies a C-string into a managed `string` struct with allocated memory.
 *
 * @param[in]  string   Input C-string to initialize from.
 * @param[in]  capacity Total allocated capacity (must be >= strlen(string) + 1).
 * @param[out] str      Pointer to the string structure to initialize.
 * 
 * @return true if successful, false on memory failure or invalid input.
 */
bool string_initialize(const char *string, const size_t capacity, struct string *str);

/**
 * @brief Updates the content and capacity of an existing string.
 *
 * Replaces the old string data with a new one, resizing the buffer.
 *
 * @param[in]  old_string   Pointer to the existing string to modify.
 * @param[in]  new_capacity New capacity to allocate.
 * @param[out] new_string   New string data to copy in.
 * 
 * @return true if successful, false otherwise.
 */
bool string_update(struct string *old_string, const size_t new_capacity, const char *new_string);

/**
 * @brief Allocates tokens for string_split().
 * 
 * @param[in] number_of_strings Number of strings to allocate for. 
 * @param[in] string_size       Length of the longest string.
 * 
 * @return Dynamically allocated tokens if successful, NULL otherwise.
 */
char **allocate_tokens(const unsigned int number_of_strings, const unsigned int string_length);

/**
 * @brief Frees tokens allocated by allocate_tokens().
 * 
 * @param[in] number_of_strings Number of strings allocated.
 * @param[in] tokens            Previously allocated tokens.
 */
void free_tokens(const unsigned int number_of_strings, char **tokens);

/**
 * @brief Splits a string with tokens allocated by allocate_tokens().
 * 
 * @param[in] strr      Pointer to the string struct.
 * @param[in] delimiter Delimiter for splitting the string.
 * @param[in] tokens    Caller allocated container for tokens.
 * 
 * @return true if successful, false otherwise.
 */
bool string_split(const struct string *strr, const char *delimiter, char **tokens);

/**
 * @brief Prints the string to standard output.
 *
 * @param[in] strr Pointer to the string to print.
 */
void string_print_string(const struct string *strr);

/**
 * @brief Compares two strings for equality.
 *
 * @param[in] strr1 Pointer to the first string.
 * @param[in] strr2 Pointer to the second string.
 * 
 * @return true if both strings are equal in content and length, false otherwise.
 */
bool string_compare(const struct string *strr1, const struct string *strr2);

/**
 * @brief Concatenates two strings and stores the result in a third string.
 *
 * The output string must be preallocated with enough capacity.
 *
 * @param[in]  strr1      Pointer to the first string.
 * @param[in]  strr2      Pointer to the second string.
 * @param[in]  capacity   Capacity of the output string buffer.
 * @param[out] out_string Pointer to the result string structure.
 * 
 * @return true if concatenation succeeded, false on capacity/memory failure.
 */
bool string_add(const struct string *strr1, const struct string *strr2, const size_t capacity, struct string *out_string);

/**
 * @brief Extracts a substring from a string.
 *
 * Copies a range of characters into a new string structure.
 *
 * @param[in]  strr      Pointer to the source string.
 * @param[in]  start     Starting index of the substring (0-based).
 * @param[in]  length    Number of characters to extract.
 * @param[out] substring Pointer to caller allocated string struct.
 * 
 * @return true if the substring was successfully extracted, false if out of bounds.
 */
bool string_substring(const struct string *strr, const size_t start, const size_t length, struct string *substring);

/**
 * @brief Deinitializes string.
 *
 * @param[in] strr Pointer to the string structure to free.
 * 
 * @return true if memory was successfully freed, false otherwise.
 */
bool string_deinitialize(struct string *strr);