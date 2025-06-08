#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "common.h"

/**
 * Reads a string input from stdin into a caller-provided buffer.
 * 
 * @param msg    The prompt message to display (cannot be NULL).
 * @param out    Buffer to store the result (must be at least `max_length + 1` bytes).
 * @param max_length Maximum length of input (excluding null terminator).
 * @return       true on success, false on error.
 */
bool get_string_input(const char *msg, char *out, const size_t max_length)
{
    if (!msg || !out || max_length == 0) {
        fprintf(stderr, "Invalid arguments to get_string_input\n");
        return false;
    }

    printf("%s", msg);
    fflush(stdout);

    if (!fgets(out, max_length + 1, stdin)) {  // +1 for null terminator
        if (feof(stdin)) {
            fprintf(stderr, "EOF reached, no input\n");
        } else {
            fprintf(stderr, "failed to read input\n");
        }
        return false;
    }

    // Remove trailing newline (if any)
    out[strcspn(out, "\n")] = '\0';

    // If input was too long, clear remaining characters from stdin
    if (strlen(out) == max_length && out[max_length - 1] != '\0') {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }

    return true;
}

/**
 * Reads an integer input from stdin.
 * 
 * @param msg    The prompt message to display (cannot be NULL).
 * @param out    Pointer to store the integer result (cannot be NULL).
 * @return       true on success, false on error.
 */
bool get_int_input(const char *msg, int *out)
{
    if (!msg || !out) {
        fprintf(stderr, "Invalid arguments to get_int_input\n");
        return false;
    }

    char buffer[32];  // Large enough for any reasonable integer input
    if (!get_string_input(msg, buffer, sizeof(buffer) - 1)) {
        return false;  // Error already handled by get_string_input
    }

    // Attempt to convert input to integer
    char *endptr = NULL;
    long val = strtol(buffer, &endptr, 10);

    // Validate conversion results
    bool conversion_error = (endptr == buffer || *endptr != '\0');
    bool range_error = (val < INT_MIN || val > INT_MAX);

    if (conversion_error || range_error) {
        if (conversion_error) {
            fprintf(stderr, "Invalid number input: '%s'\n", buffer);
        } else {
            fprintf(stderr, "Number out of int range: %ld\n", val);
        }
        return false;
    }

    *out = (int)val;
    return true;
}