#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

struct string {
    char *str;
    size_t size;
    size_t capacity;
};

#define NULL_STRING (struct string){NULL, 0, 0}

struct string create_string(const char *input, const size_t capacity);
bool update_string(struct string *old_string, const char *new_string, const size_t new_capacity);
void print_tokens(const struct string *strr);
void print_string(const struct string *strr);
bool compare_string(const struct string *strr1, const struct string *strr2);
struct string add_string(const struct string *strr1, const struct string *strr2, const size_t capacity);
struct string substring(const struct string *strr, const size_t start, const size_t length);
bool free_string(struct string *strr);