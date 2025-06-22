#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "common.h"

bool get_string_input(const char *msg, const size_t max_length, char *out)
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

bool parse_unsigned_long(const char *str, unsigned long *out)
{
    if (!str || !out) return false;

    char *endptr = NULL;
    unsigned long val = strtoul(str, &endptr, 10);
    if (*endptr != '\0' || val > UINT_MAX) return false;

    *out = val;
    return true;
}