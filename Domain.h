#pragma once

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Activitate {
private:

	int id;
	string titlu;
	string descriere;
	string tip;
	int durata;

public:

	/*Activitate& operator=(const Activitate& ot) {
		id = ot.id;
		titlu = ot.titlu;
		descriere = ot.descriere;
		tip = ot.tip;
		durata = ot.durata;
		return *this;
	}*/

	Activitate() = default;

	Activitate(int id, string titlu, string descriere, string tip, int durata) : id{ id }, titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {

	}

	Activitate(const Activitate& act) : id{ act.id }, titlu{ act.titlu }, descriere{ act.descriere }, tip{ act.tip }, durata{ act.durata } {
	
	}

	int get_id() const;
	/*
		returneaza id-ul unei activitati
	*/

	string get_titlu() const;
	/*
		returneaza titlul unei activitati
	*/

	string get_descriere() const;
	/*
		returneaza descrierea unei activitati
	*/

	string get_tip() const;
	/*
		returneaza tipul unei activitati
	*/

	int get_durata() const;
	/*
		returneaza durata unei activitati
	*/

	void set_id(int id_nou);
	/*
		seteaza id-ul unei activitati cu unul dat ca parametru
	*/

	void set_titlu(string titlu_nou);
	/*
		schimba titlul unei activitati cu unul dat ca paramtru
	*/

	void set_descriere(string descriere_noua);
	/*
		schimba descrierea unei activitati cu una data ca parametru
	*/

	void set_tip(string tip_nou);
	/*
		schimba tipul unei activitati cu unul dat ca parametru
	*/

	void set_durata(int durata_noua);
	/*
		schimba durata unei activitati cu una data ca parametru
	*/

};

void test_activitate();
/*
	functie de test pentru obiectul activitate
*/