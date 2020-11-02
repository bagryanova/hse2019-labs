#include "clist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

const int SZ = 100;

struct point {
	int x, y;
	struct intrusive_node node;
};

void add_point(struct intrusive_list *l, int x, int y) {
    assert(l != NULL);
	struct point *cur= (struct point *)malloc(sizeof(struct point));
    assert(cur != NULL);
    cur->x = x;
    cur->y = y;
    cur->node.next = NULL;
    cur->node.prev = NULL;
    add_node(l, &cur->node);
}

void remove_point(struct intrusive_list *l, int x, int y) {
    assert(l != NULL);
    struct intrusive_node *cur = l->head->next;
    while (cur != NULL) {
        struct point* p = CONTAINER_OF(cur, struct point, node);
        cur = cur->next;
        if (p->x == x && p->y == y) {
            remove_node(l, &p->node);
            free(p);
        }
    }
}

void show_all_points(struct intrusive_list *l) {
    assert(l != NULL);
    struct intrusive_node *cur = l->head->next;
    while (cur != NULL) {
        struct point* p = CONTAINER_OF(cur, struct point, node);
        printf("(%d %d) ", p->x, p->y);
        cur = cur->next;
    }
    printf("\n");
}

void remove_all_points(struct intrusive_list *l) {
    assert(l != NULL);
    struct intrusive_node *cur = l->head->next;
    while (cur != NULL) {
        struct point* p = CONTAINER_OF(cur, struct point, node);
        cur = cur->next;
        remove_node(l, &p->node);
        free(p);
    }
}

void remove_all(struct intrusive_list *l) {
    assert(l != NULL);
    remove_all_points(l);
    free(l);
}

int main() {
    struct intrusive_list *list = create_list();
    while (true) {
        char s[SZ];
        fgets(s, SZ - 1, stdin);
        char *com = strtok(s, " ");
        if (strcmp(com, "add") == 0) {
            int x = atoi(strtok(NULL, " "));
            int y = atoi(strtok(NULL, " "));
            add_point(list, x, y);
        } else if (strcmp(com, "rm") == 0) {
            int x = atoi(strtok(NULL, " "));
            int y = atoi(strtok(NULL, " "));
            remove_point(list, x, y);
        } else if (strcmp(com, "print\n") == 0) {
            show_all_points(list);
        } else if (strcmp(com, "rma\n") == 0) {
            remove_all_points(list);
        } else if (strcmp(com, "len\n") == 0) {
            printf("%d\n", get_length(list));
        } else if (strcmp(com, "exit") == 0 || strcmp(com, "exit\n") == 0) {
            remove_all(list);
            break;
        } else {
            printf("Unknown command\n");
        }
    }
    return 0;
}