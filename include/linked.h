#pragma once

typedef struct linked {
	void * p;
	struct linked * next;
	struct linked * back;
} linked_t;

typedef struct slinked {
	void * p;
	struct slinked * next;
} slinked_t;

typedef int (* linked_callback_t)(linked_t * node, void * pass);

linked_t * linked_leaf(linked_t * bottom); // find last node
linked_t * linked_branch(linked_t * node); // find first node
int linked_count(linked_t * bottom); // count nodes
linked_t * linked_add(linked_t * bottom, void * p); // create a new list if bottom == NULL, or append to the existing list
linked_t * linked_append(linked_t * bottom, linked_t * node); // adds a new node
linked_t * linked_get(linked_t * bottom, int index); // gets node at index
linked_t * linked_remove(linked_t * bottom, int index); // `linked_delete` node at index
linked_t * linked_delete(linked_t * node); // removes node from list and frees
linked_t * linked_pop(linked_t * node); // removes node but don't free
linked_t * linked_shift(linked_t * node, linked_t ** out);
void linked_iterate(linked_t * bottom, linked_callback_t callback, void * pass); // call `callback` for every node in list
linked_t * linked_find(linked_t * bottom, linked_callback_t callback, void * pass); // from branch to leaf
linked_t * linked_find_back(linked_t * bottom, linked_callback_t callback, void * pass); // from leaf to branch
void linked_destroy_all(linked_t * bottom, linked_callback_t destroy, void * pass); // free all elements in a list, call `destroy` before freeing each node

// callback for `linked_iterate` which compares `node->p` to `pass`
int linked_find_generic(linked_t * node, void * pass);
