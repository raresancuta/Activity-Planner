#pragma once

#include "Controller.h"

class ActivitateConsole {
private:

	ActivitateController& ctr;

public:

	ActivitateConsole(ActivitateController& ctr) :ctr{ ctr } {

	}
	ActivitateConsole(const ActivitateConsole& ot) = delete;

	void print_menu();
	/*
		afiseaza meniul aplicatiei
	*/

	void print_lista();
	/*
		se afiseaza lista de activitati
	*/

	void adaugare();
	/*
		se adauga o activitate
	*/

	void modificare();
	/*
		se modifica o activitate
	*/

	void stergere();
	/*
		se sterge o activitate
	*/

	void cautare();
	/*
		se cauta o activitate
	*/

	void filtrare();
	/*
		se filtreaza dupa descriere sau tip
	*/

	void sortare();
	/*
		se sorteaza lista de activitati
	*/

	void print_lista_act_planif();
	/*
		afiseaza lista activitatilor planificate
	*/

	void golire_act_planif();
	/*
		goleste lista de activitati planificate
	*/

	void adaugare_act_planif();
	/*
		adauga o activitate in lista de activitati planificate
	*/

	void generare_act_planif();
	/*
		genereaza o lista de activitati planificate
	*/

	void salvare_fisier();
	/*
		se salveaza lista de activitati planficate intr-un fisier
	*/

	void raport();
	/*
		se genereaza un raport cu tipurile de activitati
	*/

	void undo();
	/*
		se realizeaza operatia de undo pentru adaugare/modificare/stergere
	*/

	void run();
	/*
		interfata aplicatiei
	*/

};