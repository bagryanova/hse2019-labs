#pragma once

#include <stdlib.h>

int my_mergesort(void* array, size_t sz, size_t elem_sz, int (*comparator)(const void*, const void*));