#include "Domain.h"

#include <assert.h>
#include <string>
using std::string;

int Activitate::get_id() const {
	return id;
}

string Activitate::get_titlu() const {
	return titlu;
}

string Activitate::get_descriere() const {
	return descriere;
}

string Activitate::get_tip() const {
	return tip;
}

int Activitate::get_durata() const {
	return durata;
}

void Activitate::set_id(int id_nou) {
	this->id = id_nou;
}

void Activitate::set_titlu(string titlu_nou) {
	this->titlu = titlu_nou;
}

void Activitate::set_descriere(string descriere_noua) {
	this->descriere = descriere_noua;
}

void Activitate::set_tip(string tip_nou) {
	this->tip = tip_nou;
}

void Activitate::set_durata(int durata_noua) {
	this->durata = durata_noua;
}

void test_activitate() {
	Activitate act{ 1,"Titlu","Descriere","Tip",1 };
	assert(act.get_id() == 1);
	assert(act.get_titlu() == "Titlu");
	assert(act.get_descriere() == "Descriere");
	assert(act.get_tip() == "Tip");
	assert(act.get_durata() == 1);

	act.set_id(2);
	act.set_titlu("Titlu1");
	act.set_descriere("Descriere1");
	act.set_tip("Tip1");
	act.set_durata(2);
	assert(act.get_id() == 2);
	assert(act.get_titlu() == "Titlu1");
	assert(act.get_descriere() == "Descriere1");
	assert(act.get_tip() == "Tip1");
	assert(act.get_durata() == 2);
}