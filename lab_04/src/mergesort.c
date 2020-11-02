#include <stdlib.h>
#include <assert.h>


void* get_val_by_pos(void* array, size_t pos, size_t elem_sz, size_t sz) {
	assert(array != NULL);
	assert(pos < sz);
	return (void *)((char *)array + pos * elem_sz);
}

void swap(void* first, void* second, size_t elem_sz) {
	assert(first != NULL);
	assert(second != NULL);
	for (size_t i = 0; i < elem_sz; ++i) {
		char cur = *((char *)first + i);
		*((char *)first + i) = *((char *)second + i);
		*((char *)second + i) = cur;
	}
}

int my_mergesort(void* array, size_t sz, size_t elem_sz, int (*comparator)(const void*, const void*)) {
	if (sz <= 1) {
		return 0;
	}
	size_t sz1 = sz / 2, sz2 = sz - sz1;
	void* first = array;
	void* second = get_val_by_pos(array, sz1, elem_sz, sz);
	if (my_mergesort(first, sz1, elem_sz, comparator) == -1) {
		return -1;
	}
	if (my_mergesort(second, sz2, elem_sz, comparator) == -1) {
		return -1;
	} 
	void* buf = malloc(elem_sz * sz);
	if (buf == NULL) {
		return -1;
	}
	size_t u1 = 0, u2 = 0, u = 0;
	while (u1 < sz1 || u2 < sz2) {
		if (u1 < sz1 && (u2 == sz2 || comparator(get_val_by_pos(first, u1, elem_sz, sz1), get_val_by_pos(second, u2, elem_sz, sz2)) < 0)) {
			swap(get_val_by_pos(first, u1, elem_sz, sz1), get_val_by_pos(buf, u, elem_sz, sz), elem_sz);
			++u1;
		} else {
			swap(get_val_by_pos(second, u2, elem_sz, sz2), get_val_by_pos(buf, u, elem_sz, sz), elem_sz);
			++u2;
		}
		++u;
	}
	for (size_t i = 0; i < sz; ++i) {
		swap(get_val_by_pos(array, i, elem_sz, sz), get_val_by_pos(buf, i, elem_sz, sz), elem_sz);
	}
	free(buf);
	return 0;
}
