#pragma once
#include "Domain.h"
#include <vector>
using std::vector;

class ValidatorException {
private:
	vector<string> erori;
public:
	ValidatorException(vector<string> erori) :erori{ erori } {

	}
	vector<string>& get_erori();
	/*
		returneaza mesajul exceptiei
	*/
};

class Validator {
public:
	void validare(const Activitate& act);
	/*
		valideaza obiectul act
	*/

};