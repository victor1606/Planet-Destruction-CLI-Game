# Copyright 2021 Calugaritoiu Ion-Victor

build:
	gcc -Wall -Wextra -std=c99 functions.c CircularDoublyLinkedList.c main.c -o main
clean:
	rm -rf main
