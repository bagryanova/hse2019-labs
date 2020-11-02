#pragma once

#define OFFSETOF(type, member) ((long)&(((type*)0)->member))

#define CONTAINER_OF(ptr, type, member) (type*)((char*)(ptr) - OFFSETOF(type, member))

struct intrusive_node {
	struct intrusive_node *next;
	struct intrusive_node *prev;
};

struct intrusive_list {
	struct intrusive_node *head;
};

void init_list(struct intrusive_list *l);

struct intrusive_list* create_list(void);

void add_node(struct intrusive_list *l, struct intrusive_node *node);

void remove_node(struct intrusive_list *l, struct intrusive_node *node);

int get_length(struct intrusive_list *l);