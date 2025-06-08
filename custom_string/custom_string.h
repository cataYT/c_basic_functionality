#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

struct string {
    char *str;
    size_t size;
    size_t capacity;
};

bool create_string(const char *string, const size_t capacity, struct string *str);
bool update_string(struct string *old_string, const size_t new_capacity, const char *new_string);
void print_tokens(const struct string *strr);
void print_string(const struct string *strr);
bool compare_string(const struct string *strr1, const struct string *strr2);
bool add_string(const struct string *strr1, const struct string *strr2, const size_t capacity, struct string *out_string);
bool substring(const struct string *strr, const size_t start, const size_t length, struct string *substring);
bool free_string(struct string *strr);