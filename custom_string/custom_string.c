#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "custom_string.h"

struct string create_string(const char *input, const size_t capacity)
{
    if (input == NULL || strlen(input) == 0) {
        fprintf(stderr, "string cannot be formed from null char *\n");
        return NULL_STRING;
    }

    if (capacity == 0) {
        fprintf(stderr, "capacity cannot be 0\n");
        return NULL_STRING;
    }

    size_t input_size = strlen(input);

    if (input_size > capacity) {
        fprintf(stderr, "size cannot be greater than capacity\n");
        return NULL_STRING;
    }

    struct string strr = NULL_STRING;
    strr.str = malloc(input_size + 1);
    if (!strr.str) {
        perror("malloc failed");
        return NULL_STRING;
    }
    strr.size = input_size;
    strr.capacity = capacity;
    strcpy(strr.str, input);
    return strr;
}

bool update_string(struct string *old_string, const char *new_string, const size_t new_capacity)
{
    if (!old_string) {
        fprintf(stderr, "old string is null at update_string()");
        return false;
    }

    size_t ns_size = strlen(new_string);

    if (new_string == NULL || ns_size == 0) {
        fprintf(stderr, "new string cannot be null");
        return false;
    }

    if (new_capacity <= 0) {
        fprintf(stderr, "new capacity cannot be 0 or negative");
        return false;
    }
    
    if (ns_size > new_capacity) {
        fprintf(stderr, "Error: new string size exceeds capacity\n");
        return false;
    }

    char *new_str = realloc(old_string->str, new_capacity);
    if (!new_str) {
        fprintf(stderr, "realloc failed.\n");
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
        fprintf(stderr, "string is empty, cannot print tokens\n");
        return;
    }
    
    // Make a writable copy of the string so strtok doesn't modify original
    char *temp = malloc(strr->size + 1);
    if (!temp) {
        fprintf(stderr, "malloc failed");
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
        fprintf(stderr, "string is null, cannot print");
        return;
    }
    printf("%s\n", strr->str);
    return;
}

bool compare_string(const struct string *strr1, const struct string *strr2)
{
    if (!strr1) {
        fprintf(stderr, "string 1 is NULL in compare_string()\n");
        return false;
    }

    if (!strr2) {
        fprintf(stderr, "string 2 is NULL in compare_string()\n");
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

struct string add_string(const struct string *strr1, const struct string *strr2, const size_t capacity)
{
    if (!strr1 || strr1->size == 0) {
        fprintf(stderr, "string 1 is null or empty at add_string()\n");
        return NULL_STRING;
    }

    if (!strr2 || strr2->size == 0) {
        fprintf(stderr, "string 2 is null or empty at add_string()\n");
        return NULL_STRING;
    }

    if ((strr1->size + strr2->size) > capacity) {
        fprintf(stderr, "size of both is larger than capacity\n");
        return NULL_STRING;
    }

    struct string new_str = NULL_STRING;

    // Allocate enough space for concatenated string + null terminator
    new_str.str = malloc(strr1->size + strr2->size + 1);
    if (!new_str.str) {
        fprintf(stderr, "malloc failed at add_string()\n");
        return NULL_STRING;
    }

    // Copy strr1's string bytes
    strcpy(new_str.str, strr1->str);

    // Append strr2's string safely
    strcat(new_str.str, strr2->str);

    new_str.size = strr1->size + strr2->size;
    new_str.capacity = capacity;

    return new_str;
}

struct string substring(const struct string *strr, const size_t start, const size_t length)
{
    if (!strr || strr->size == 0) {
        fprintf(stderr, "string is null or empty at substring()\n");
        return NULL_STRING;
    }

    if (start >= strr->size) {
        fprintf(stderr, "start index out of range at substring()\n");
        return NULL_STRING;
    }

    size_t max_len = strr->size - start;
    size_t sub_len = (length > max_len) ? max_len : length;

    if (sub_len == 0) {
        fprintf(stderr, "substring length is zero after adjustment\n");
        return NULL_STRING;
    }

    struct string sub_str = NULL_STRING;
    sub_str.str = malloc(sub_len + 1);
    if (!sub_str.str) {
        fprintf(stderr, "malloc failed at substring()\n");
        return NULL_STRING;
    }

    memcpy(sub_str.str, strr->str + start, sub_len);
    sub_str.str[sub_len] = '\0';

    sub_str.size = sub_len;

    return sub_str;
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