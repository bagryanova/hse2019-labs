#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "point_list.h"

int from_int_to_coordinate(uint8_t* array) {
    assert(array != NULL);
    int result = ((int)array[2] << 16) + ((int)array[1] << 8) + array[0];
    if (((int)array[2] >> 7) == 1) {
        result = ~result;
        result ^= (1 << 24) - 1;
    }
    return result;
}

void from_coordinate_to_int(int val, uint8_t* array) {
    assert(array != NULL);
    for (size_t i = 0; i < 3; ++i) {
        array[i] = (val & ((1 << 8) - 1));
        val = (val >> 8);
    }
}

void print(intrusive_node* node, void* data) {
    assert(node != NULL);
    assert(data != NULL);
    point_node* point = get_point(node);
    assert(point != NULL);
    printf((char*)data, point->x, point->y);
}

void count(intrusive_node* node, void* data) {
    assert(node != NULL);
    assert(data != NULL);
    (*((int*)data))++;
}

void load_text(char* name, intrusive_list* list) {
    assert(name != NULL);
    assert(list != NULL);
    FILE* in = fopen(name, "r");
    assert(in != NULL);
    int x, y;
    while (fscanf(in, "%d %d", &x, &y) >= 0) {
        add_point(list, x, y);
    }
    fclose(in);
} 

void save_text(char* name, intrusive_list* list) {
    assert(name != NULL);
    assert(list != NULL);
    FILE* out = fopen(name, "w");
    assert(out != NULL);
    intrusive_node* cur = list->head.next;
    while (cur != &list->head) {
        point_node* point = get_point(cur);
        assert(point != NULL);
        fprintf(out, "%d %d\n", point->x, point->y);
        cur = cur->next;
    }
    fclose(out);
}

void load_bin(char* name, intrusive_list* list) {
    assert(name != NULL);
    assert(list != NULL);
    FILE* in = fopen(name, "rb");
    assert(in != NULL);
    uint8_t x[3] = {0};
    uint8_t y[3] = {0};
    while (fread(x, sizeof(x[0]), 3, in) > 0) {
        fread(y, sizeof(y[0]), 3, in);
        add_point(list, from_int_to_coordinate(x), from_int_to_coordinate(y));
    }
    fclose(in);
}

void save_bin(char* name, intrusive_list* list) {
    assert(name != NULL);
    assert(list != NULL);
    FILE* out = fopen(name, "wb");
    assert(out != NULL);
    intrusive_node* cur = list->head.next;
    while (cur != &list->head) {
        point_node* point = get_point(cur);
        assert(point != NULL);
        uint8_t x[3] = {0};
        uint8_t y[3] = {0};
        from_coordinate_to_int(point->x, x);
        from_coordinate_to_int(point->y, y);
        fwrite(x, sizeof(x[0]), 3, out);
        fwrite(y, sizeof(y[0]), 3, out);
        cur = cur->next;
    }
    fclose(out);
}

int main(int argc, char* argv[]) {
    assert(argc > 3);
    intrusive_list list;
    init_list(&list);
    assert(&list != NULL);
    if (strcmp(argv[1], "loadtext") == 0) {
        load_text(argv[2], &list);
    } else {
        load_bin(argv[2], &list);
    }
    char* act = argv[3];
    if (strcmp(act, "savetext") == 0) {
        save_text(argv[4], &list);
    }
    if (strcmp(act, "savebin") == 0) {
        save_bin(argv[4], &list);
    }
    if (strcmp(act, "print") == 0) {
        apply(&list, print, argv[4]);
    }
    if (strcmp(act, "count") == 0) {
        int cnt = 0;
        apply(&list, count, &cnt);
        printf("%d\n", cnt);
    }
    remove_all_points(&list);
    return 0;
}