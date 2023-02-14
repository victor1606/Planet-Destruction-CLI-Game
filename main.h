// Copyright 2021 Calugaritoiu Ion-Victor

#ifndef MAIN_H_
#define MAIN_H_

#include "CircularDoublyLinkedList.h"

typedef struct value value;
struct value {
	char *planet_name;
	doubly_linked_list_t *shields;
	int kills;
};

void add_planet(doubly_linked_list_t *galaxy);
void blh_planet(doubly_linked_list_t *galaxy, unsigned int index);
void upg_planet(doubly_linked_list_t *galaxy);
void exp_planet(doubly_linked_list_t *galaxy);
void rmv_planet(doubly_linked_list_t *galaxy);
void col_planet(doubly_linked_list_t *galaxy);
void rot_planet(doubly_linked_list_t *galaxy);
void shw_planet(doubly_linked_list_t *galaxy);
void free_planets(doubly_linked_list_t **galaxy);

#endif  // MAIN_H_
