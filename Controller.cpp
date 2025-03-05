#include "Controller.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <exception>
using std::cout;
using std::fstream;
using std::ios;

vector<Activitate>& ActivitateController::getAll() {
	return repo.getAll();
}

void ActivitateController::adauga(int id, string titlu, string descriere, string tip, int durata) {
	Activitate act{ id,titlu,descriere,tip,durata };
	val.validare(act);
	repo.stocheaza(act);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, act));
}

void ActivitateController::modifica(int id, string titlu, string descriere, string tip, int durata) {
	Activitate act{ id,titlu,descriere,tip,durata };
	val.validare(act);
	const Activitate& act_repo = repo.cauta(id);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, act_repo));
	repo.modifica(act);
}

void ActivitateController::sterge(int id) {
	const Activitate& act =repo.cauta(id);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, act));
	repo.sterge(id);
}

void ActivitateController::undo() {
	if (undoActions.empty()) {
		throw std::exception("Nu mai exista operatii");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

const Activitate& ActivitateController::cauta(int id) {
	return repo.cauta(id);
}

const Activitate& ActivitateController::cauta_titlu(string titlu) {
	return repo.cauta_titlu(titlu);
}

void ActivitateController::filtreaza(vector<Activitate>& l_filtr, int tip_filtru, string filtru) {
	if (tip_filtru == 1)
		repo.filtrare_descriere(l_filtr, filtru);
	else if (tip_filtru == 2)
		repo.filtrare_tip(l_filtr, filtru);
}

void ActivitateController::sortare(int tip_sort, int ord) {
	repo.sortare(tip_sort, ord);
}

const vector<Activitate>& ActivitateController::get_all_act_planif() {
	return act_planif.get_all();
}

void ActivitateController::delete_act_planif() {
	act_planif.delete_all();
	notify();
}

void ActivitateController::adauga_act_planif(string titlu) {
	auto& act = repo.cauta_titlu(titlu);
	act_planif.stocheaza(act);
	notify();
}

/*string ActivitateController::random_cuvant(int len) {
	const string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, int(CHARACTERS.size() - 1));

	string random_string;

	for (int i = 0; i < len; ++i)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}
int ActivitateController::random_int(int size) {
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, size - 1);
	return distribution(generator);
}*/

void ActivitateController::generare_act_random(int nr_activitati) {
	act_planif.generare_act_planif(nr_activitati, repo.getAll());
	notify();
}

void ActivitateController::save_to_csv(string fisier) {
	const auto& activitati = act_planif.get_all();
	fstream fout;
	fout.open(fisier, ios::out | ios::trunc);
	for (const Activitate& act : activitati) {
		fout << act.get_id() << "," << act.get_titlu() << "," << act.get_descriere() << "," << act.get_tip() << "," << act.get_durata() << "\n";
	}
	fout.close();
}

void ActivitateController::save_to_html(string fisier) {
	const auto& activitati = act_planif.get_all();
	std::ofstream out(fisier, std::ios::trunc);
	out << "<html><body>" << endl;
	out << "<table border=\"1\" style=\"width:100% \">" << endl;
	for (const auto& act : activitati) {
		out << "<tr>" << std::endl;
		out << "<td>" << act.get_id() << "</td>" << endl;
		out << "<td>" << act.get_titlu() << "</td>" << endl;
		out << "<td>" << act.get_descriere() << "</td>" << endl;
		out << "<td>" << act.get_tip() << "</td>" << endl;
		out << "<td>" << act.get_durata() << "</td>" << endl;
		out << "</tr>" << endl;
	}
	out << "</table>" << endl;
	out << "</body></html>" << endl;
	out.close();
}
void ActivitateController::raport(unordered_map<string, int>& rap) {
	return repo.raport(rap);
}

void test_ctr() {
	ActivitateRepository repo;
	Validator val;
	ActivitatiPlanificateRepository act_planif{ repo };
	ActivitateController ctr{ repo ,act_planif,val};

	// test adaugare
	ctr.adauga(1, "T", "D", "T", 1);
	const auto& activitati = ctr.getAll();
	assert(activitati.size() == 1);
	try {
		ctr.adauga(2, "t1", "d1", "t1", 1);
	}
	catch (ValidatorException& ot) {
		vector<string> erori = ot.get_erori();
	}

	// test modificare
	ctr.modifica(1, "t", "t", "t", 2);
	try {
		ctr.modifica(2, "T", "T", "T", 2);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

	// test cautare
	const Activitate& act = ctr.cauta(1);
	assert(act.get_id() == 1);
	assert(act.get_titlu() == "t");
	assert(act.get_descriere() == "t");
	assert(act.get_tip() == "t");
	assert(act.get_durata() == 2);

	const Activitate& act5 = ctr.cauta_titlu("t");
	assert(act5.get_id() == 1);

	// test stergere
	ctr.sterge(1);
	assert(activitati.size() == 0);
	try {
		ctr.sterge(1);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}

	// test filtrare
	ctr.adauga(1, "titlu_unu", "descr_unu", "tip_unu", 1);
	ctr.adauga(2, "titlu_doi", "descr_doi", "tip_doi", 5);
	ctr.adauga(3, "titlu_trei", "descr_unu", "tip_doi", 1);
	vector<Activitate> l_filtr;
	ctr.filtreaza(l_filtr, 1, "descr_unu");
	assert(l_filtr.size() == 2);
	auto& act1 = l_filtr[0];
	assert(act1.get_titlu() == "titlu_unu");
	auto& act2 = l_filtr[1];
	assert(act2.get_titlu() == "titlu_trei");
	for (int i = 1; i <= 2; i++) {
		auto iterator = l_filtr.begin();
		l_filtr.erase(iterator);
	}
	assert(l_filtr.size() == 0);
	ctr.filtreaza(l_filtr, 2, "tip_doi");
	assert(l_filtr.size() == 2);
	auto& act3 = l_filtr[0];
	assert(act3.get_titlu() == "titlu_doi");
	auto& act4 = l_filtr[1];
	assert(act4.get_titlu() == "titlu_trei");

	// test sortare
	ctr.sortare(1, 1);
	assert(activitati[0].get_titlu() == "titlu_doi");
	assert(activitati[1].get_titlu() == "titlu_trei");
	assert(activitati[2].get_titlu() == "titlu_unu");

	ctr.sortare(1, 2);
	assert(activitati[2].get_titlu() == "titlu_doi");
	assert(activitati[1].get_titlu() == "titlu_trei");
	assert(activitati[0].get_titlu() == "titlu_unu");

	ctr.sortare(2, 1);
	assert(activitati[0].get_descriere() == "descr_doi");
	assert(activitati[1].get_descriere() == "descr_unu");
	assert(activitati[2].get_descriere() == "descr_unu");

	ctr.sortare(2, 2);
	assert(activitati[2].get_descriere() == "descr_doi");
	assert(activitati[1].get_descriere() == "descr_unu");
	assert(activitati[0].get_descriere() == "descr_unu");

	ctr.sortare(3, 1);
	assert(activitati[0].get_durata() == 1);
	assert(activitati[1].get_durata() == 5);
	assert(activitati[2].get_durata() == 1);

	ctr.sortare(3, 2);
	assert(activitati[2].get_durata() == 1);
	assert(activitati[1].get_durata() == 5);
	assert(activitati[0].get_durata() == 1);

	ctr.adauga_act_planif("titlu_unu");
	const auto& activitati1 = ctr.get_all_act_planif();
	assert(activitati1.size() == 1);
	assert(activitati1[0].get_id() == 1);
	assert(activitati1[0].get_titlu() == "titlu_unu");
	assert(activitati1[0].get_descriere() == "descr_unu");
	assert(activitati1[0].get_tip() == "tip_unu");
	assert(activitati1[0].get_durata() == 1);
	ctr.adauga_act_planif("titlu_doi");
	assert(activitati1.size() == 2);
	try {
		ctr.adauga_act_planif("titlu_patru");
	}
	catch (ExceptieRepository& ot) {
		assert(ot.get_msg().size() != 0);
	}
	ctr.delete_act_planif();
	assert(activitati1.size() == 0);
	try {
		ctr.generare_act_random(4);
	}
	catch (ExceptieRepository&) {
		assert(true);
	}
	ctr.generare_act_random(3);
	assert(activitati1.size() == 3);
	ctr.delete_act_planif();

	// test fisier
	ctr.adauga_act_planif("titlu_unu");
	ctr.save_to_csv("fiser_test.csv");
	ctr.save_to_html("fisier_test.html");
	fstream f;
	string act7;
	f.open("fiser_test.csv", ios::in );
	f >> act7;
	assert (act7 == "1,titlu_unu,descr_unu,tip_unu,1");
	f.close();

	
	// test raport
	unordered_map<string, int> rap;
	ctr.raport(rap);
	assert(rap["tip_unu"] == 1);
	assert(rap["tip_doi"] == 2);

	// test undo
	ctr.undo();
	assert(activitati.size() == 2);
	assert(activitati[1].get_titlu() == "titlu_doi");
	ctr.modifica(2, "titlu_trei", "desc_doi", "tip_doi", 5);
	assert(activitati[1].get_titlu() == "titlu_trei");
	ctr.undo();
	assert(activitati[1].get_titlu() == "titlu_doi");
	ctr.sterge(2);
	assert(activitati.size() == 1);
	ctr.undo();
	assert(activitati.size() == 2);
	assert(activitati[1].get_titlu() == "titlu_doi");
}