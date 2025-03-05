#include "Repository.h"
#include <assert.h>
#include <exception>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
using std::cout;

vector<Activitate>& ActivitateRepository::getAll() {
	return elems;
}

void ActivitateRepository::stocheaza(const Activitate& act) {
	bool caut_act = exista(act.get_id());
	if (caut_act)
		throw ExceptieRepository("Activitate deja existenta in memorie!");
	else elems.push_back(act);
}

bool ActivitateRepository::exista(int id) {
	for (const Activitate& act : elems) {
		if (act.get_id() == id)
			return 1;
	}
	return 0;
}

const Activitate& ActivitateRepository::cauta(int id) {
	for (const Activitate& act : elems) {
		if (act.get_id() == id)
			return act;
	}
	throw ExceptieRepository("Activitatea cu id-ul dat nu exista in memorie!");
}


void ActivitateRepository::modifica(const Activitate& act) {
	bool caut_act = exista(act.get_id());
	if (!caut_act)
		throw ExceptieRepository("Activitatea cu id-ul dat nu exista in memorie!");
	else {
		for (Activitate& act_it : elems) {
			if (act_it.get_id() == act.get_id()) {
				act_it.set_titlu(act.get_titlu());
				act_it.set_descriere(act.get_descriere());
				act_it.set_tip(act.get_tip());
				act_it.set_durata(act.get_durata());
			}
		}
	}
}

void ActivitateRepository::sterge(int id) {
	bool caut_act = exista(id);
	if (!caut_act)
		throw ExceptieRepository("Activitatea cu id-ul dat nu exista in memorie!");
	else {
		bool ok = false;
		for (auto iterator = elems.begin(); iterator != elems.end() && !ok; ++iterator) {
			if ((*iterator).get_id() == id) {
				elems.erase(iterator);
				ok = true;
			}
			if (ok == true)
				break;
		}
	}
}

const Activitate& ActivitateRepository::cauta_titlu(string titlu) {
	auto act = std::find_if(elems.begin(), elems.end(), [titlu](const Activitate& act) {
		return act.get_titlu() == titlu;
		});
	if (act == elems.end())
		throw ExceptieRepository("Nu exista activitate cu titlul dat ");
	return *act;
}

void ActivitateRepository::filtrare_descriere(vector<Activitate>& l_filtr, string descriere) {
	std::copy_if(elems.begin(), elems.end(), std::back_inserter(l_filtr),[descriere](const Activitate& act) {
			return act.get_descriere() == descriere;
		});
}

void ActivitateRepository::filtrare_tip(vector<Activitate>& l_filtr, string tip) {
	std::copy_if(elems.begin(), elems.end(), std::back_inserter(l_filtr), [tip](const Activitate& act) {
		return act.get_tip() == tip;
		});
}

void ActivitateRepository::sortare(int tip_sort, int ord) {
	if (tip_sort == 1)
		sort(elems.begin(), elems.end(), [ord](const Activitate& act1, const Activitate& act2) {
		if (ord == 1)
			return act1.get_titlu() < act2.get_titlu();
		else return act1.get_titlu() > act2.get_titlu();
			});
	else if (tip_sort == 2)
		sort(elems.begin(), elems.end(), [ord](const Activitate& act1, const Activitate& act2) {
		if (ord == 1)
			return act1.get_descriere() < act2.get_descriere();
		else return act1.get_descriere() > act2.get_descriere();
			});
	else if (tip_sort == 3)
		sort(elems.begin(), elems.end(), [ord](const Activitate& act1, const Activitate& act2) {
		if (ord == 1)
			return (act1.get_tip() < act2.get_tip() || (act1.get_tip() == act2.get_tip() && act1.get_durata() < act2.get_durata()));
		else return (act1.get_tip() > act2.get_tip() || (act1.get_tip() == act2.get_tip() && act1.get_durata() > act2.get_durata()));
			});
}
const vector<Activitate>& ActivitatiPlanificateRepository::get_all() {
	return act_planif;
}

void ActivitatiPlanificateRepository::delete_all() {
	act_planif.clear();
}

void ActivitatiPlanificateRepository::stocheaza(const Activitate& act) {
	act_planif.push_back(act);
}

void ActivitatiPlanificateRepository::generare_act_planif(int nr_activitati,vector<Activitate> activitati) {
	if (nr_activitati > activitati.size())
		throw ExceptieRepository("Numar prea mare de activitati");
	std::shuffle(activitati.begin(), activitati.end(), std::default_random_engine(std::random_device{}())); 
	while (act_planif.size() < nr_activitati && activitati.size() > 0) {
		act_planif.push_back(activitati.back());
		activitati.pop_back();
	}
}

bool ActivitateRepository::cauta_in_raport(unordered_map<string,int>& rap,string tip) {
	unordered_map<string, int>::iterator it = rap.begin();
	while (it != rap.end()) {
		if (it->first == tip)
			return 1;
		++it;
	}
	return 0;
}
void ActivitateRepository::raport(unordered_map<string,int>& rap) {
	for (const Activitate& act : elems) {
		if (!cauta_in_raport(rap, act.get_tip()))
			rap[act.get_tip()] = 1;
		else rap[act.get_tip()] = rap[act.get_tip()] + 1;
	}
}

void ActivitateFileRepository::write_in_file() {
	std::ofstream out(file);
	const auto& activitati = getAll();
	for (const Activitate& act : activitati) {
		out << act.get_id() << endl << act.get_titlu() << endl << act.get_descriere() << endl << act.get_tip() << endl << act.get_durata() << endl;
	}
	out.close();
}

void ActivitateFileRepository::read_from_file() {
	std::ifstream in(file);
	while (!in.eof()) {
		int id, durata;
		string titlu, descriere, tip;
		in >> id >> titlu >> descriere >> tip >> durata;
		if (in.eof())
			break;
		Activitate act{ id,titlu,descriere,tip,durata };
		stocheaza(act);
	}
	in.close();
}

void ActivitateFileRepository::stocheaza(const Activitate& act) {
	ActivitateRepository::stocheaza(act);
	write_in_file();
}

void ActivitateFileRepository::modifica(const Activitate& act) {
	ActivitateRepository::modifica(act);
	write_in_file();
}

void ActivitateFileRepository::sterge(int id) {
	ActivitateRepository::sterge(id);
	write_in_file();
}

void ActivitateFileRepository::sortare(int tip_sort, int ord) {
	ActivitateRepository::sortare(tip_sort,ord);
	write_in_file();
}

string ExceptieRepository::get_msg() {
	return msg;
}

void test_repo() {
	ActivitateRepository repo;

	// test stocare
	Activitate act{ 1,"T1","D1","T1",1 };
	repo.stocheaza(act);
	const auto& activitati = repo.getAll();
	assert(activitati.size() == 1);
	auto& act1 = activitati[0];
	assert(act1.get_id() == 1);
	assert(act1.get_titlu() == "T1");
	assert(act1.get_descriere() == "D1");
	assert(act1.get_tip() == "T1");
	assert(act1.get_durata() == 1);

	try {
		repo.stocheaza(act);
		//assert(false);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

	//test modificare
	Activitate act2{ 1,"T2","D2","T1",2 };
	repo.modifica(act2);
	//auto& activitati1 = repo.getAll();
	auto& act3 = activitati[0];

	assert(act3.get_id() == 1);
	assert(act3.get_titlu() == "T2");
	assert(act3.get_descriere() == "D2");
	assert(act3.get_tip() == "T1");
	assert(act3.get_durata() == 2);

	Activitate act4{2,"T2","D2","T1",2};
	try {
		repo.modifica(act4);
		//assert(false);
	}
	catch (ExceptieRepository& ot) {

		assert(ot.get_msg().length() != 0);
	}
	//test cautare
	const Activitate& act5 = repo.cauta(1);
	assert(act5.get_id() == 1);
	assert(act5.get_titlu() == "T2");
	assert(act5.get_descriere() == "D2");
	assert(act5.get_tip() == "T1");
	assert(act5.get_durata() == 2);

	try {
		repo.cauta(2);
		//assert(false);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

	//test stergere
	repo.sterge(1);
	//const auto& activitati2 = repo.getAll();
	assert(activitati.size() == 0);

	try {
		repo.sterge(1);
		//assert(false);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

}
void test_repo_file() {
	ActivitateFileRepository repo{ "act_test.txt" };
	const auto& activitati = repo.getAll();
	assert(activitati.size() == 0);
	// test stocare
	repo.stocheaza(Activitate{ 1,"T1","D1","T1",1 });
	assert(activitati.size() == 1);

	ActivitateFileRepository repo_1{ "act_test.txt" };
	const auto& activitati_1 = repo_1.getAll();
	assert(activitati_1.size() == 1);

	// test modificare
	repo.modifica(Activitate{ 1,"T2","D2","T1",2 });
	ActivitateFileRepository repo_2{ "act_test.txt" };
	const auto& activitati_2 = repo_2.getAll();
	assert(activitati_2[0].get_titlu() == "T2");

	// test sortare
	repo.sortare(1, 1);
	assert(activitati_2[0].get_titlu() == "T2");

	// test stergere
	repo.sterge(1);
	ActivitateFileRepository repo_3{ "act_test.txt" };
	const auto& activitati_3 = repo_3.getAll();
	assert(activitati_3.size() == 0);
}

vector<Activitate>& LabRepo::getAll() {
	unordered_map<int, Activitate>::iterator it = elems.begin();
	vect.clear();
	while (it != elems.end()) {
		vect.push_back(it->second);
		++it;
	}
	return vect;
}

void LabRepo::stocheaza(const Activitate& act) {
	bool caut_act = exista(act.get_id());
	if (caut_act)
		throw ExceptieRepository("Activitate deja existenta in memorie!");
	else elems.insert(std::pair<int,Activitate>(act.get_id(),act));
}

bool LabRepo::exista(int id) {
	unordered_map<int,Activitate>::iterator it = elems.begin();
	while (it != elems.end()) {
		if (it->first == id)
			return 1;
		++it;
	}
	return 0;
}

const Activitate& LabRepo::cauta(int id) {
	unordered_map<int, Activitate>::iterator it = elems.find(id);
	if (it == elems.end())
		throw ExceptieRepository("Activitatea cu id - ul dat nu exista in memorie!");
	return it->second;
}


void LabRepo::modifica(const Activitate& act) {
	bool caut_act = exista(act.get_id());
	if (!caut_act)
		throw ExceptieRepository("Activitatea cu id-ul dat nu exista in memorie!");
	else {
		unordered_map<int, Activitate>::iterator it = elems.begin();
		while (it != elems.end()) {
			if (it->first == act.get_id()) {
				it->second = act;
			}
			++it;
		}
	}
}

void LabRepo::sterge(int id) {
	bool caut_act = exista(id);
	if (!caut_act)
		throw ExceptieRepository("Activitatea cu id-ul dat nu exista in memorie!");
	else {
		bool ok = false;
		unordered_map<int, Activitate>::iterator it = elems.begin();
		while (it != elems.end()) {
			if (it->first == id) {
				elems.erase(it);
				ok = true;
			}
			if (ok == true)
				break;
			++it;
		}
	}
}

const Activitate& LabRepo::cauta_titlu(string titlu) {
	unordered_map<int, Activitate>::iterator it = elems.begin();
	while (it != elems.end()) {
		if (it->second.get_titlu() == titlu) {
			break;
		}
		++it;
	}
	if(it == elems.end())
		throw ExceptieRepository("Nu exista activitate cu titlul dat ");
	return it->second;
}

void LabRepo::filtrare_descriere(vector<Activitate>& l_filtr, string descriere) {
	l_filtr.clear();
	unordered_map<int, Activitate>::iterator it = elems.begin();
	while (it != elems.end()) {
		if (it->second.get_descriere() == descriere)
			l_filtr.push_back(it->second);
		++it;
	}
}

void LabRepo::filtrare_tip(vector<Activitate>& l_filtr, string tip) {
	l_filtr.clear();
	unordered_map<int, Activitate>::iterator it = elems.begin();
	while (it != elems.end()) {
		if (it->second.get_tip() == tip)
			l_filtr.push_back(it->second);
		++it;
	}
}

void LabRepo::sortare(int tip_sort, int ord) {
	vect.clear();
	unordered_map<int, Activitate>::iterator it = elems.begin();
	while (it != elems.end()) {
		vect.push_back(it->second);
		++it;
	}
	if (tip_sort == 1)
		sort(vect.begin(), vect.end(), [ord](const Activitate& act1, const Activitate& act2) {
		if (ord == 1)
			return act1.get_titlu() < act2.get_titlu();
		else return act1.get_titlu() > act2.get_titlu();
			});
	else if (tip_sort == 2)
		sort(vect.begin(), vect.end(), [ord](const Activitate& act1, const Activitate& act2) {
		if (ord == 1)
			return act1.get_descriere() < act2.get_descriere();
		else return act1.get_descriere() > act2.get_descriere();
			});
	else if (tip_sort == 3)
		sort(vect.begin(), vect.end(), [ord](const Activitate& act1, const Activitate& act2) {
		if (ord == 1)
			return (act1.get_tip() < act2.get_tip() || (act1.get_tip() == act2.get_tip() && act1.get_durata() < act2.get_durata()));
		else return (act1.get_tip() > act2.get_tip() || (act1.get_tip() == act2.get_tip() && act1.get_durata() > act2.get_durata()));
			});
	elems.clear();
	for (auto& act : vect) {
		elems.insert(pair<int, Activitate>(act.get_id(), act));
	}
}

bool LabRepo::cauta_in_raport(unordered_map<string, int>& rap, string tip) {
	unordered_map<string, int>::iterator it = rap.begin();
	while (it != rap.end()) {
		if (it->first == tip)
			return 1;
		++it;
	}
	return 0;
}
void LabRepo::raport(unordered_map<string, int>& rap) {
	unordered_map<int, Activitate>::iterator it = elems.begin();
	while (it != elems.end()) {
		if (!cauta_in_raport(rap, it->second.get_tip()))
			rap[it->second.get_tip()] = 1;
		else rap[it->second.get_tip()] = rap[it->second.get_tip()] + 1;
		++it;
	}
}
void test_lab_repo() {
	LabRepo repo;

	// test adaugare
	repo.stocheaza(Activitate{ 1, "T", "D", "T", 1 });
	const auto& activitati = repo.getAll();
	assert(activitati.size() == 1);
	try {
		repo.stocheaza(Activitate{ 1, "t1", "d1", "t1", 1 });
	}
	catch (ExceptieRepository& ot) {
		auto erori = ot.get_msg();
	}

	// test modificare
	repo.modifica(Activitate{ 1, "t", "t", "t", 2 });
	try {
		repo.modifica(Activitate{ 2, "T", "T", "T", 2 });
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

	// test cautare
	const Activitate& act = repo.cauta(1);
	assert(act.get_id() == 1);
	assert(act.get_titlu() == "t");
	assert(act.get_descriere() == "t");
	assert(act.get_tip() == "t");
	assert(act.get_durata() == 2);
	try {
		repo.cauta(2);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

	const Activitate& act1 = repo.cauta_titlu("t");
	assert(act1.get_id() == 1);
	try {
		repo.cauta_titlu("t1");
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

	// test stergere
	repo.stocheaza(Activitate{ 2, "T", "T", "T", 2 });
	repo.sterge(2);
	const auto& activitati1 = repo.getAll();
	assert(activitati1.size() == 1);
	try {
		repo.sterge(2);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}
	repo.sterge(1);

	// test filtrare
	repo.stocheaza(Activitate{ 1, "titlu_unu", "descr_unu", "tip_unu", 1 });
	repo.stocheaza(Activitate{ 2, "titlu_doi", "descr_doi", "tip_doi", 5 });
	repo.stocheaza(Activitate{ 3, "titlu_trei", "descr_unu", "tip_doi", 1 });
	vector<Activitate> l_filtr;
	repo.filtrare_descriere(l_filtr,"descr_unu");
	assert(l_filtr.size() == 2);
	assert(l_filtr[0].get_titlu() == "titlu_unu");
	assert(l_filtr[1].get_titlu() == "titlu_trei");
	
	repo.filtrare_tip(l_filtr,"tip_doi");
	assert(l_filtr.size() == 2);
	assert(l_filtr[0].get_titlu() == "titlu_doi");
	assert(l_filtr[1].get_titlu() == "titlu_trei");

	// test sortare
	repo.sortare(1, 1);
	const auto& activitati2 = repo.getAll();
	assert(activitati2[0].get_titlu() == "titlu_doi");
	assert(activitati2[1].get_titlu() == "titlu_trei");
	assert(activitati2[2].get_titlu() == "titlu_unu");

	repo.sortare(1, 2);
	const auto& activitati3 = repo.getAll();
	assert(activitati3[2].get_titlu() == "titlu_doi");
	assert(activitati3[1].get_titlu() == "titlu_trei");
	assert(activitati3[0].get_titlu() == "titlu_unu");

	repo.sortare(2, 1);
	const auto& activitati4 = repo.getAll();
	assert(activitati4[0].get_descriere() == "descr_doi");
	assert(activitati4[1].get_descriere() == "descr_unu");
	assert(activitati4[2].get_descriere() == "descr_unu");

	repo.sortare(2, 2);
	const auto& activitati5 = repo.getAll();
	assert(activitati5[2].get_descriere() == "descr_doi");
	assert(activitati5[1].get_descriere() == "descr_unu");
	assert(activitati5[0].get_descriere() == "descr_unu");

	repo.sortare(3, 1);
	const auto& activitati6 = repo.getAll();
	assert(activitati6[0].get_durata() == 1);
	assert(activitati6[1].get_durata() == 5);
	assert(activitati6[2].get_durata() == 1);

	repo.sortare(3, 2);
	const auto& activitati7 = repo.getAll();
	assert(activitati7[2].get_durata() == 1);
	assert(activitati7[1].get_durata() == 5);
	assert(activitati7[0].get_durata() == 1);

	// test raport
	unordered_map<string, int> rap;
	repo.raport(rap);
	assert(rap["tip_unu"] == 1);
	assert(rap["tip_doi"] == 2);

}