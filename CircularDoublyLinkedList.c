// Copyright 2021 Calugaritoiu Ion-Victor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

// noua lista este alocata si parametrii sunt initializati
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
	doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
	DIE(!list, "List malloc failed.");

	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;

	return list;
}

// returneaza nodul aflat la pozitia n
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	DIE(!list, "List is NULL.");
	DIE(!list->head, "List is empty.");

	n = n % list->size;

	dll_node_t *target = list->head;
	for (unsigned int i = 0; i < n; i++)
		target = target->next;

	return target;
}

// adauga nodul cu valoarea data pe pozitia n in lista
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
	DIE(!list, "List is NULL.");

	if (n > list->size)
		n = list->size;

	dll_node_t *new_node = malloc(sizeof(dll_node_t));
	DIE(!new_node, "New_node malloc failed.");

	new_node->data = malloc(list->data_size);
	DIE(!new_node->data, "New_node->data malloc failed.");

	memcpy(new_node->data, data, list->data_size);

	if (!list->head) {
		list->head = new_node;
		list->head->prev = list->head->next = list->head;
	} else if (n == 0) {
		new_node->next = list->head;
		new_node->prev = list->head->prev;

		list->head->prev->next = new_node;
		list->head->prev = new_node;

		list->head = new_node;
	} else {
		dll_node_t *prev_node = list->head;

		for (unsigned int i = 0; i < n - 1; i++)
			prev_node = prev_node->next;

		new_node->next = prev_node->next;
		new_node->prev = prev_node;
		prev_node->next->prev = new_node;
		prev_node->next = new_node;
	}

	list->size++;
}

// sterge nodul aflat pe pozitia n din lista
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	DIE(!list, "List is NULL.");
	DIE(!list->head, "List is empty.");

	if (n >= list->size)
		n = list->size - 1;

	dll_node_t *removed = list->head;
	for (unsigned int i = 0; i < n; i++)
		removed = removed->next;

	removed->prev->next = removed->next;
	removed->next->prev = removed->prev;

	if (n == 0) {
		if (list->size == 1)
			list->head = NULL;
		else
			list->head = list->head->next;
	}
	list->size--;

	return removed;
}

// returneaza numarul de noduri din lista
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
	DIE(!list, "List is NULL.");
	return list->size;
}

// elibereaza toata memoria utilizata de lista
void
dll_free(doubly_linked_list_t** pp_list)
{
	DIE(!pp_list, "List is NULL.");
	DIE(!(*pp_list), "*list is NULL");

	doubly_linked_list_t *list = *pp_list;

	dll_node_t *curr = list->head;
	for (unsigned int i = 0; i < list->size; i++) {
		dll_node_t *removed = curr;
		curr = curr->next;
		free(removed->data);
		free(removed);
	}
	free(list);
	*pp_list = NULL;
}

// printeaza valorile nodurilor din lista
void
dll_print_int_list(doubly_linked_list_t* list)
{
	DIE(!list, "List is NULL.");

	dll_node_t *curr = list->head;
	for (unsigned int i = 0; i < list->size; i++) {
		printf("%d ", *((int *) curr->data));
		curr = curr->next;
	}
	printf("\n");
}
