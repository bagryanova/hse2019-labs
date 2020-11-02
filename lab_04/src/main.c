#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int int_comparator(const void* first, const void* second) {
    assert(first != NULL);
    assert(second != NULL);
    return *(const int*)first - *(const int*)second;
}

int char_comparator(const void* first, const void* second) {
    assert(first != NULL);
    assert(second != NULL);
    return *(const char*)first - *(const char*)second;
}

int string_comparator(const void* first, const void* second) {
    assert(first != NULL);
    assert(second != NULL);
    return strcmp(*(const char**)first, *(const char**)second);
}

int int_sort(int* array, size_t sz) {
    assert(array != NULL);
    if (my_mergesort(array, sz, sizeof(int), int_comparator) == -1) {
        return -1;
    }
    for (size_t i = 0; i < sz; ++i) {
        printf("%d ", array[i]);
    }
    return 0;
}

int char_sort(char* array, size_t sz) {
    assert(array != NULL);
    if (my_mergesort(array, sz, sizeof(char), char_comparator) == -1) {
        return -1;
    }
    for (size_t i = 0; i < sz; ++i) {
        printf("%c ", array[i]);
    }
    return 0;
}

int string_sort(char** array, size_t sz) {
    assert(array != NULL);
    if (my_mergesort(array, sz, sizeof(char*), string_comparator) == -1) {
        return -1;
    }
    for (size_t i = 0; i < sz; ++i) {
        printf("%s ", array[i]);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    char* type = argv[1];
    int sz = argc - 2;
    if (sz == 0) {
        return 0;
    }
    if (*type == 'i') {
        int* array = (int*)malloc(sizeof(int) * sz);
        assert(array != NULL);
        for (int i = 2; i < argc; ++i) {
            array[i - 2] = atoi(argv[i]);
        }
        if (int_sort(array, sz) == -1) {
            printf("Error: memory allocation failed");
            return 1;
        }
        free(array);
    }
    if (*type == 'c') {
        char* array = (char*)malloc(sizeof(char) * sz);
        assert(array != NULL);
        for (int i = 2; i < argc; ++i) {
            array[i - 2] = *argv[i];
        }
        if (char_sort(array, sz) == -1) {
            printf("Error: memory allocation failed");
            return 1;
        }
        free(array);
    }
    if (*type == 's') {
        if (string_sort(&argv[2], sz) == -1) {
            printf("Error: memory allocation failed");
            return 1;
        }
    }
    return 0;
}