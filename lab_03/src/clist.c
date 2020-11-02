#include "clist.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

bool contains(struct intrusive_list *l, struct intrusive_node *node) {
	struct intrusive_node *cur = l->head->next;
	bool find = false;
	while (cur != NULL && !find) {
		if (cur == node) {
			find = true;
		}
		++cur;
	}
	return find;
}

void init_list(struct intrusive_list *l) {
	assert(l != NULL);
	l->head = (struct intrusive_node*)malloc(sizeof(struct intrusive_node));
	assert(l->head != NULL);
	l->head->prev = NULL;
	l->head->next = NULL;
	return; 
}

struct intrusive_list* create_list(void) {
	struct intrusive_list *l = (struct intrusive_list *)malloc(sizeof(struct intrusive_list));
	assert(l != NULL);
	init_list(l);
	return l;
}

void add_node(struct intrusive_list *l, struct intrusive_node *node) {
	assert(l != NULL);
	assert(node != NULL);
	node->next = l->head->next;
	node->prev = l->head;
	if (l->head->next != NULL) {
		l->head->next->prev = node;
	} 
	l->head->next = node;
}

void remove_node(struct intrusive_list *l, struct intrusive_node *node) {
	assert(l != NULL);
	assert(node != NULL);
	assert(contains(l, node) == true);
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	node->prev->next = node->next;
}

int get_length(struct intrusive_list *l) {
	assert(l != NULL);
	int res = 0;
	struct intrusive_node *cur = l->head->next;
	while (cur != NULL) {
		++res;
		cur = cur->next;
	}
	return res;
}