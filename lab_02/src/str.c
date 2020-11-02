#include <stdio.h>
#include "str.h"

char* my_strcpy(char* restrict s1, const char* restrict s2) {
    char* res = s1;
    while (*s2 != '\0') {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
    return res;
}

char* my_strcat(char* restrict s1, const char* restrict s2) {
    char* res = s1;
    while (*s1 != '\0') {
        s1++;
    }
    while (*s2 != '\0') {
        *s1 = *s2;
        s1++;
        s2++;
    }
    return res;
}

int my_strcmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 == *s2) {
            s1++;
            s2++;
            continue;
        }
        return *s1 - *s2;
    }
    return *s1 - *s2;
}

size_t my_strlen(const char* s) {
    size_t res = 0;
    while (*s != '\0') {
        s++;
        res++;
    }
    return res;
}



