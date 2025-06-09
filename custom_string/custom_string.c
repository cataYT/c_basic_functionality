#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "custom_string.h"

bool create_string(const char *string, const size_t capacity, struct string *str)
{
    if (string == NULL || string[0] == '\0') {
        fprintf(stderr, "string is null at create_string()\n");
        return false;
    }

    if (capacity == 0) {
        fprintf(stderr, "capacity is 0 at create_string()\n");
        return false;
    }

    size_t string_size = strlen(string);

    if (string_size > capacity) {
        fprintf(stderr, "size is greater than capacity at create_string()\n");
        return false;
    }

    memset(str, 0, sizeof(*str));

    str->str = malloc(string_size + 1);
    if (!str->str) {
        fprintf(stderr, "malloc failed at create_string()\n");
        return false;
    }
    str->size = string_size;
    str->capacity = capacity;
    strcpy(str->str, string);

    return true;
}

bool update_string(struct string *old_string, const size_t new_capacity, const char *new_string)
{
    if (!old_string) {
        fprintf(stderr, "old string is null at update_string()\n");
        return false;
    }

    size_t ns_size = strlen(new_string);

    if (new_string == NULL || ns_size == 0) {
        fprintf(stderr, "new string is null at update_string()\n");
        return false;
    }

    if (new_capacity == 0) {
        fprintf(stderr, "new capacity is 0 at update_string()\n");
        return false;
    }
    
    if (ns_size > new_capacity) {
        fprintf(stderr, "size is larger than capacity at update_string()\n");
        return false;
    }

    char *new_str = realloc(old_string->str, new_capacity);
    if (!new_str) {
        fprintf(stderr, "realloc failed at update_string()\n");
        return false;
    }

    strcpy(new_str, new_string);

    old_string->str = new_str;
    old_string->size = ns_size;
    old_string->capacity = new_capacity;

    return true;
}

void print_tokens(const struct string *strr)
{
    if (!strr->str) {
        fprintf(stderr, "string is null at print_tokens()\n");
        return;
    }
    
    // Make a writable copy of the string so strtok doesn't modify original
    char *temp = malloc(strr->size + 1);
    if (!temp) {
        fprintf(stderr, "malloc failed at print_tokens()\n");
        return;
    }

    strcpy(temp, strr->str); // include '\0'

    char *token = strtok(temp, " ");
    while (token) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " ");
    }

    free(temp);
}

void print_string(const struct string *strr)
{
    if (!strr->str) {
        fprintf(stderr, "string is null at print_string()\n");
        return;
    }
    printf("%s\n", strr->str);
    return;
}

bool compare_string(const struct string *strr1, const struct string *strr2)
{
    if (!strr1) {
        fprintf(stderr, "string 1 is null at compare_string()\n");
        return false;
    }

    if (!strr2) {
        fprintf(stderr, "string 2 is null at compare_string()\n");
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

bool add_string(const struct string *strr1, const struct string *strr2, const size_t capacity, struct string *out_string)
{
    if (!strr1 || strr1->size == 0) {
        fprintf(stderr, "string 1 is null or empty at add_string()\n");
        return false;
    }

    if (!strr2 || strr2->size == 0) {
        fprintf(stderr, "string 2 is null or empty at add_string()\n");
        return false;
    }

    if ((strr1->size + strr2->size) > capacity) {
        fprintf(stderr, "size of both is larger than capacity\n");
        return false;
    }

    memset(out_string, 0, sizeof(*out_string));

    // Allocate enough space for concatenated string + null terminator
    out_string->str = malloc(strr1->size + strr2->size + 1);
    if (!out_string->str) {
        fprintf(stderr, "malloc failed at add_string()\n");
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

bool substring(const struct string *strr, const size_t start, const size_t length, struct string *substring)
{
    if (!strr || strr->size == 0) {
        fprintf(stderr, "string is null or empty at substring()\n");
        return false;
    }

    if (start >= strr->size) {
        fprintf(stderr, "start index out of range at substring()\n");
        return false;
    }

    size_t max_len = strr->size - start;
    size_t sub_len = (length > max_len) ? max_len : length;

    if (sub_len == 0) {
        fprintf(stderr, "substring length is zero after adjustment at substring()\n");
        return false;
    }

    memset(substring, 0, sizeof(*substring));

    substring->str = malloc(sub_len + 1);
    if (!substring->str) {
        fprintf(stderr, "malloc failed at substring()\n");
        return false;
    }

    memcpy(substring->str, strr->str + start, sub_len);
    substring->str[sub_len] = '\0';

    substring->size = sub_len;

    return true;
}

bool free_string(struct string *strr)
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