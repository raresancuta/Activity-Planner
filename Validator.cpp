#include "Validator.h"
#include <string.h>


void Validator::validare(const Activitate& act) {
	vector<string>erori;

	string titlu = act.get_titlu();
	for (unsigned int i = 0; i < titlu.length(); i++)
		if (titlu[i] >= '0' && titlu[i] <= '9') {
			erori.push_back("Titlu invalid");
			break;
		}
	string descriere = act.get_descriere();
	for (unsigned int i = 0; i < descriere.length(); i++)
		if (descriere[i] >= '0' && descriere[i] <= '9') {
			erori.push_back("Descriere invalida");
			break;
		}
	string tip = act.get_tip();
	for (unsigned int i = 0; i < tip.length(); i++)
		if (tip[i] >= '0' && tip[i] <= '9') {
			erori.push_back("Tip invalid");
			break;
		}
	if (erori.size() > 0)
		throw ValidatorException(erori);
}

vector<string>& ValidatorException::get_erori() {
	return erori;
}