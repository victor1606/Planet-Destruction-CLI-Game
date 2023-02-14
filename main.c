// Copyright 2021 Calugaritoiu Ion-Victor

#include <stdio.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "main.h"

#define CMD_LEN 4

int main()
{
	int nr_actions;
	char command[CMD_LEN];

	doubly_linked_list_t *galaxy = dll_create(sizeof(value));

	scanf("%d", &nr_actions);

	for (int i = 0; i < nr_actions; ++i) {		// citesc n comenzi
		scanf("%s", command);

		if (!strcmp(command, "ADD"))
			add_planet(galaxy);
		else if (!strcmp(command, "BLH"))
		{
			int index;
			scanf("%d", &index);
			blh_planet(galaxy, index);
		}
		else if (!strcmp(command, "UPG"))
			upg_planet(galaxy);
		else if (!strcmp(command, "EXP"))
			exp_planet(galaxy);
		else if (!strcmp(command, "RMV"))
			rmv_planet(galaxy);
		else if (!strcmp(command, "COL"))
			col_planet(galaxy);
		else if (!strcmp(command, "ROT"))
			rot_planet(galaxy);
		else if (!strcmp(command, "SHW"))
			shw_planet(galaxy);
	}
	// eliberez toate datele, scuturile si planetele galaxiei
	free_planets(&galaxy);

	return 0;
}
