#pragma once

#include "Repository.h"
#include "Validator.h"
#include "Undo.h"
#include "Observer.h"
using std::unique_ptr;

class ActivitateController :public Observable {
private:

	Repo& repo;
	Validator& val;
	ActivitatiPlanificateRepository& act_planif;
	vector<unique_ptr<ActiuneUndo>> undoActions;

public:

	ActivitateController(Repo& repo, ActivitatiPlanificateRepository& act_planif, Validator& val) : repo{ repo }, act_planif{ act_planif }, val{ val } {

	}
	ActivitateController(const ActivitateController& ot) = delete;

	vector<Activitate>& getAll();
	/*
		returneaza lista de activitati
	*/

	void adauga(int id, string titlu, string descriere, string tip, int durata);
	/*
		se adauga o activitate noua cu specificatiile date ca parametru
	*/

	void modifica(int id, string titlu, string descriere, string tip, int durata);
	/*
		se modifica activitatea cu id-ul dat ca parametru din memorie cu
		specificatiile noi
	*/

	void sterge(int id);
	/*
		se sterge activitatea cu id-ul data ca parametru din memorie
	*/

	void undo();
	/*
		se efectueaza operatia de undo
	*/

	const Activitate& cauta(int id);
	/*
		se returneaza activitatea cu id-ul dat ca parametru din memorie
	*/

	const Activitate& cauta_titlu(string titlu);
	/*
		se returneaza activitatea cu titlul dat ca parametru
	*/

	void filtreaza(vector<Activitate>& l_filtr, int tip_filtru, string filtru);
	/*
		realizeaza operatiunea de filtrare dupa un filtru dat ca parametru codificat
		1 -> filtrare dupa descriere, 2-> filtrare dupa tip
	*/

	void sortare(int tip_sort, int ord);
	/*
		sorteaza lista dupa detaliile  si ordinea dorita a activitatilor

		tip_sort:
		1 -> titlu
		2 -> descriere
		3 -> tip + durata
		ord:
		1-> cresc
		2-> descresc

	*/

	const vector<Activitate>& get_all_act_planif();
	/*
		returneaza lista de activitati planificate
	*/

	void delete_act_planif();
	/*
		sterge toate activitatile planificate selectate
	*/

	void adauga_act_planif(string titlu);
	/*
		adauga in lista de activitati curente activitatea cu titlul
		dat ca parametru
	*/

	//string random_cuvant(int len);
	/*
		genereaza un cuvant cu dimensiunea data ca parametru
	*/

	//int random_int(int size);
	/*
		genereaza un int cu dimensiunea data ca parametru 
	*/

	void generare_act_random(int nr_activitati);
	/*
		adauga in lista de activitati planificate un numar finit de
		activitati cu specificatii aleatorii
	*/

	void save_to_csv(string fisier);
	/*
		salveaza lista de activitati planificate intr-un fisier csv
	*/

	void save_to_html(string fisier);
	/*
		salveaza lista de activitati planificate intr-un fisier html
	*/

	void raport(unordered_map<string,int>& rap);
	/*
		creeaza un raport cu toate activitatile de un anumit tip si frecventa activitatilor
		cu acel tip
	*/
};

void test_ctr();
/*
	se testeaza controller-ul managerului de activitati
*/