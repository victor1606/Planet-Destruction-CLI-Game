// Copyright 2021 Calugaritoiu Ion-Victor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "main.h"
#include "utils.h"

#define BUF_LEN 21

void add_planet(doubly_linked_list_t *galaxy)
{
	unsigned int index, nr_shields;

	char p_name[BUF_LEN];
	scanf("%s %d %d", p_name, &index, &nr_shields);

	if(galaxy->size < index) {
		printf("Planet out of bounds!\n");
		return;
	}

	value *info = malloc(sizeof(value));
	DIE(!info, "Info malloc failed.");
	info->planet_name = malloc(sizeof(p_name));
	DIE(!info->planet_name, "Info malloc failed.");
	// copiez structura cu informatiile planetelor
	memcpy(info->planet_name, p_name, strlen(p_name) + 1);

	info->shields = dll_create(sizeof(int));

	int def = 1;

	for (unsigned int i = 0; i < nr_shields; ++i)
		dll_add_nth_node(info->shields, i, &def);		// adaug fiecare scut

	info->kills = 0;

	dll_add_nth_node(galaxy, index, info);		// adaug fiecare planeta

	printf("The planet %s has joined the galaxy.\n", p_name);
	free(info);		// eliberez structura care a fost deja copiata
}

void free_planets(doubly_linked_list_t **galaxy)
{
	dll_node_t* curr_planet = (*galaxy)->head;
	dll_node_t* temp_planet;
	// parcurg si eliberez campurile alocate pentru fiecare planeta
	for(unsigned int i = 0; i < (*galaxy)->size; ++i) {
		temp_planet = curr_planet;
		curr_planet = curr_planet->next;

		free(((value *)temp_planet->data)->planet_name);
		doubly_linked_list_t *shields = ((value *)temp_planet->data)->shields;
		dll_free(&shields);		// eliberez lista de scuturi
	}

	dll_free(galaxy); 	// eliberez lista de planete
	*galaxy = NULL;
}

void shw_planet(doubly_linked_list_t *galaxy)
{
	unsigned int index;
	scanf("%d", &index);

	if(index >= galaxy->size || galaxy->size == 0) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *planet = dll_get_nth_node(galaxy, index);

	printf("NAME: %s\n", ((value *)planet->data)->planet_name);
	// printez datele despre planeta cu indicele dat ca parametru
	if(galaxy->size == 1)
		printf("CLOSEST: none\n");
		else if (galaxy->size == 2)
			printf("CLOSEST: %s\n", ((value *)planet->prev->data)->planet_name);
			else
				printf("CLOSEST: %s and %s\n", ((value *)planet->prev->data)->planet_name,
				((value *)planet->next->data)->planet_name);

	printf("SHIELDS: ");		// printez lista de scuturi
	dll_print_int_list(((value *)planet->data)->shields);
	printf("KILLED: %d\n", ((value *)planet->data)->kills);
}

void blh_planet(doubly_linked_list_t *galaxy, unsigned int index)
{
	if(index >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *planet = dll_remove_nth_node(galaxy, index);
	// verific daca planeta a fost distrusa in urma unei coliziuni
	if(((value *)planet->data)->kills != -1)		// daca nu, printez mesajul:
		printf("The planet %s has been eaten by the vortex.\n",
		((value *)planet->data)->planet_name);

	doubly_linked_list_t *shields = ((value *)planet->data)->shields;
	dll_free(&shields);		// eliberez lista de scuturi
	free(((value *)planet->data)->planet_name);
	free(planet->data);
	free(planet);
}

void upg_planet(doubly_linked_list_t *galaxy)
{
	unsigned int p_index, s_index, upg_value;

	scanf("%d %d %d", &p_index, &s_index, &upg_value);

	if(p_index >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *planet = dll_get_nth_node(galaxy, p_index);

	if(s_index >= ((value *)planet->data)->shields->size) {
		printf("Shield out of bounds!\n");
		return;
	}

	dll_node_t *shield;		// obtin scutul care trebuie imbunatatit
	shield = dll_get_nth_node(((value *)planet->data)->shields, s_index);

	int def = *(int *)shield->data + upg_value;
	// copiez noua valoare in campul "data" al scutului
	memcpy(shield->data, &def,
	sizeof(((value *)planet->data)->shields->data_size));
}

void exp_planet(doubly_linked_list_t *galaxy)
{
	unsigned int index, exp_val;
	scanf("%d%d", &index, &exp_val);

	if(index >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *planet = dll_get_nth_node(galaxy, index);
	// adaug un nou scut in lista de scuturi a planetei
	dll_add_nth_node(((value *)planet->data)->shields,
	((value *)planet->data)->shields->size, &exp_val);
}

void rmv_planet(doubly_linked_list_t *galaxy)
{
	unsigned int p_index, s_index;
	scanf("%d%d", &p_index, &s_index);

	if(p_index >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}
	// obtin planeta cu indexul dorit
	dll_node_t *planet = dll_get_nth_node(galaxy, p_index);

	if(s_index >= ((value *)planet->data)->shields->size) {
		printf("Shield out of bounds!\n");
		return;
	}

	if(((value *)planet->data)->shields->size == 4) {
		printf("A planet cannot have less than 4 shields!\n");
		return;
	}
	// obtin scutul dorit si il sterg din lista de scuturi a planetei
	dll_node_t *shield;
	shield = dll_remove_nth_node(((value *)planet->data)->shields, s_index);
	free(shield->data);		// eliberez scutul si valoarea sa
	free(shield);
}

void col_planet(doubly_linked_list_t *galaxy)
{
	unsigned int index_1, index_2, killed = 0;
	scanf("%d %d", &index_1, &index_2);

	if(index_1 >= galaxy->size || index_2 >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}
	// obtin cele doua planete dorite
	dll_node_t *planet_1 = dll_get_nth_node(galaxy, index_1);
	dll_node_t *planet_2 = dll_get_nth_node(galaxy, index_2);
	// obtin indicii scuturilor ce urmeaza sa scada in urma coliziunii
	int col_1 = ((value *)planet_1->data)->shields->size / 4;
	int col_2 = (((value *)planet_2->data)->shields->size / 4) * 3;

	dll_node_t *shield_1;
	shield_1 = dll_get_nth_node(((value *)planet_1->data)->shields, col_1);
	dll_node_t *shield_2;
	shield_2 = dll_get_nth_node(((value *)planet_2->data)->shields, col_2);

	(*(int *)shield_1->data)--;
	(*(int *)shield_2->data)--;
	// verific daca prima planeta a ajuns cu scutul la valoarea 0
	if(*((int *)shield_1->data) < 0 && planet_1 != NULL) {
		printf("The planet %s has imploded.\n",
		((value *)planet_1->data)->planet_name);

		if (planet_2 != NULL)
			((value *)planet_2->data)->kills++;
		// marchez planeta 1 ca fiind distrusa in urma unei coliziuni
		((value *)planet_1->data)->kills = -1;
		blh_planet(galaxy, index_1);		// sterg planeta 1 din galaxie
		killed = 1;
	}
	// verific daca a doua planeta a ajuns cu scutul la valoarea 0
	if(*((int *)shield_2->data) < 0 && planet_2 != NULL) {
		printf("The planet %s has imploded.\n",
		((value *)planet_2->data)->planet_name);

		if (planet_1 != NULL && killed == 0)
			((value *)planet_1->data)->kills++;

		if (killed == 1)
			index_2--;		// daca planeta 1 a fost distrusa, micsorez indexul planetei 2
		// marchez planeta 2 ca fiind distrusa in urma unei coliziuni
		((value *)planet_2->data)->kills = -1;
		blh_planet(galaxy, index_2);
	}
}

void rot_planet(doubly_linked_list_t *galaxy)
{
	unsigned int index, units;
	char direction;

	scanf("%d %c %d", &index, &direction, &units);

	if(direction != 't' && direction != 'c') {
		printf("Not a valid direction!\n");
		return;
	}

	if(index >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *planet = dll_get_nth_node(galaxy, index);

	if(units > ((value *)planet->data)->shields->size)
		units = units % ((value *)planet->data)->shields->size;

	if(direction == 'c')
		units = ((value *)planet->data)->shields->size - units;
	// modific pozitia nodului "head" al listei de scuturi
	dll_node_t *new_head;
	new_head = dll_get_nth_node(((value *)planet->data)->shields, units);
	((value *)planet->data)->shields->head = new_head;
}
