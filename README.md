# Planet-Destruction-CLI-Game
Planetary destruction turn-based strategy game implemented in C using generic circular doubly linked lists

Copyright 2021 Calugaritoiu Ion-Victor

- In fisierul main.c se initializeaza galaxia ce va fi modificata pe parcursul
programului, se citeste numarul de comenzi ce urmeaza a fi executate,
iar apoi se introduc instructiuni si se verifica daca acestea corespund
sintaxei functiilor; se apeleaza functiile aferente comenzilor si se modifica
continutul galaxiei si a planetelor;

- Galaxia este realizata cu ajutorul unei liste circulare dublu inlantuite
generice, planetele fiind noduri ale acesteia;
- La randul lor planetele au fost folosite pentru stocarea urmatoarelor date:
nume_planeta, numar de kill-uri si lista circulara dublu inlantuita pentru
scuturile si valorile lor;

- Se pot apela urmatoarele comenzi:
	- ADD: adauga o noua planeta in galaxie; se citesc parametrii si se
aloca memorie pentru structura info, ce contine toate datele despre planeta si
lista scuturilor sale; se copiaza aceste date in campul data al planetei si se
elibereaza structura info;

	- BLH: sterge o planeta din galaxie; se apeleaza dll_remove_nth_node
pe planeta cu indexul dorit; daca functia a fost apelata din interiorul
functiei "COL", nu se mai afiseaza "The planet has been eaten by the vortex";
se elibereaza lista de scuturi a planetei si celelalte date;

	- UPG: imbunatateste valoarea unui scut dorit cu un numar upg_value;
se obtine planeta si scutul dorit in functie de indecsii primiti, si se copiaza
noua valoare in campul data al scutului;

	- EXP: adauga planetei un scut la final cu o valoare anume; se
apeleaza functia dll_add_nth_node pentru a adauga scutul si valoarea sa;

	- RMV: sterge un scut anume din lista de scuturi a planetei; se
apeleaza dll_remove_nth_node pe scutul dorit, si se elibereaza memoria
utilizata de acesta;

	- COL: se produce o coliziune intre 2 planete dorite; se scad cu 1
valorile scutului cu indicele size/4 al primei planete si scutului de pe
pozitia size/4*3 al doilea planete; daca unul dintre scuturi ajunge la
valoarea 0, se apeleaza "BLH" pe planeta, se incrementeaza numarul de kill-uri
si se afiseaza un mesaj sugestiv;

	- ROT: scuturile planetei dorite se rotesc fie in sens trigonometric,
fie in sensul acelor de ceasornic, cu un numar de unitati; pentru a obtine
acest efect, se modifica nodul head din lista de scuturi, in functie de
numarul de unitati si de sens;

	- SHW: se afiseaza toate datele despre o planeta: numele sau, numele
vecinilor daca este cazul, lista de scuturi si numarul de kill-uri;

- Dupa finalizarea tuturor comenzilor este apelata functia free_planets,
care elibereaza toata memoria utilizata pe parcursul rularii programului;

