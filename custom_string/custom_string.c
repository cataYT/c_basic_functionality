#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "custom_string.h"

bool string_initialize(const char *string, const size_t capacity, struct string *str)
{
    if (!string || string[0] == '\0') {
        fprintf(stderr, "string is null at string_initialize()\n");
        return false;
    }

    if (capacity == 0) {
        fprintf(stderr, "capacity is 0 at string_initialize()\n");
        return false;
    }

    size_t string_size = strlen(string);

    if (string_size > capacity) {
        fprintf(stderr, "size is greater than capacity at string_initialize()\n");
        return false;
    }

    str->str = malloc(string_size + 1);
    if (!str->str) {
        fprintf(stderr, "malloc failed at string_initialize()\n");
        return false;
    }
    str->size = string_size;
    str->capacity = capacity;
    strcpy(str->str, string);

    return true;
}

bool string_update(struct string *old_string, const size_t new_capacity, const char *new_string)
{
    if (!old_string) {
        fprintf(stderr, "old string is null at string_update()\n");
        return false;
    }

    size_t ns_size = strlen(new_string);

    if (!new_string || ns_size == 0) {
        fprintf(stderr, "new string is null at string_update()\n");
        return false;
    }

    if (new_capacity == 0) {
        fprintf(stderr, "new capacity is 0 at string_update()\n");
        return false;
    }
    
    if (ns_size > new_capacity) {
        fprintf(stderr, "size is larger than capacity at string_update()\n");
        return false;
    }

    char *new_str = realloc(old_string->str, new_capacity);
    if (!new_str) {
        fprintf(stderr, "realloc failed at string_update()\n");
        return false;
    }

    strcpy(new_str, new_string);

    old_string->str = new_str;
    old_string->size = ns_size;
    old_string->capacity = new_capacity;

    return true;
}

bool string_split(const struct string *strr, const char *delimiter, char **tokens)
{
    if (!strr) {
        fprintf(stderr, "string is null at string_split()\n");
        return false;
    }

    if (!tokens) {
        fprintf(stderr, "tokens is null at string_split()\n");
        return false;
    }

    char *copy_string = malloc(strlen(strr->str) + 1);
    if (!copy_string) {
        fprintf(stderr, "malloc failed at string_split()\n");
        return false;
    }
    strcpy(copy_string, strr->str);
    char *token = strtok(copy_string, delimiter);

    unsigned int i = 0;
    while (token) {
        if (!tokens[i]) {
            fprintf(stderr, "tokens[%u] is NULL — caller must allocate each token buffer.\n", i);
            break;
        }
        strcpy(tokens[i], token);
        token = strtok(NULL, delimiter);
        i++;
    }
    free(copy_string);
    return false;
}

void string_print_string(const struct string *strr)
{
    if (!strr->str) {
        fprintf(stderr, "string is null at string_print_string()\n");
        return;
    }
    printf("%s\n", strr->str);
    return;
}

bool string_compare(const struct string *strr1, const struct string *strr2)
{
    if (!strr1) {
        fprintf(stderr, "string 1 is null at string_compare()\n");
        return false;
    }

    if (!strr2) {
        fprintf(stderr, "string 2 is null at string_compare()\n");
        return false;
    }

    if (strr1->size != strr2->size) {
        return false;
    }

    for (int i = 0; i < strr1->size; i++) {
        if (strr1->str[i] != strr2->str[i]) {
            return false;
        }
    }

    return true;
}

bool string_add(const struct string *strr1, const struct string *strr2, const size_t capacity, struct string *out_string)
{
    if (!strr1 || strr1->size == 0) {
        fprintf(stderr, "string 1 is null or empty at string_add()\n");
        return false;
    }

    if (!strr2 || strr2->size == 0) {
        fprintf(stderr, "string 2 is null or empty at string_add()\n");
        return false;
    }

    if ((strr1->size + strr2->size) > capacity) {
        fprintf(stderr, "size of both is larger than capacity at string_add()\n");
        return false;
    }

    // Allocate enough space for concatenated string + null terminator
    out_string->str = malloc(strr1->size + strr2->size + 1);
    if (!out_string->str) {
        fprintf(stderr, "malloc failed at string_add()\n");
        return false;
    }

    // Copy strr1's string bytes
    strcpy(out_string->str, strr1->str);

    // Append strr2's string safely
    strcat(out_string->str, strr2->str);

    out_string->size = strr1->size + strr2->size;
    out_string->capacity = capacity;

    return true;
}

bool string_substring(const struct string *strr, const size_t start, const size_t length, struct string *substring)
{
    if (!strr || strr->size == 0) {
        fprintf(stderr, "string is null or empty at string_substring()\n");
        return false;
    }

    if (start >= strr->size) {
        fprintf(stderr, "start index out of range at string_substring()\n");
        return false;
    }

    size_t max_len = strr->size - start;
    size_t sub_len = (length > max_len) ? max_len : length;

    if (sub_len == 0) {
        fprintf(stderr, "substring length is zero after adjustment at string_substring()\n");
        return false;
    }

    substring->str = malloc(sub_len + 1);
    if (!substring->str) {
        fprintf(stderr, "malloc failed at string_substring()\n");
        return false;
    }

    memcpy(substring->str, strr->str + start, sub_len);
    substring->str[sub_len] = '\0';

    substring->size = sub_len;

    return true;
}

bool string_deinitialize(struct string *strr)
{
    if (!strr->str) {
        return false;
    }

    free(strr->str);
    strr->str = NULL;
    strr->size = 0;
    strr->capacity = 0;

    return true;
}