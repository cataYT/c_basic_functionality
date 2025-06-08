#pragma once

#include <stdbool.h>
#include <stdlib.h>

// must free it
bool get_string_input(const char *msg, char *out, const size_t length);
// check out value if successful
bool get_int_input(const char *msg, int *out);