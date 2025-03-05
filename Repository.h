#pragma once

//#include "VectorTemplate.h"
#include <exception>
#include <vector>
#include <unordered_map>
#include "Domain.h"
#include <string>
using std::vector;
using std::unordered_map;
using std::pair;

class Repo {
public:
	//Repo(double prob) {
		//throw ExceptieRepository(std::to_string(prob));
	//}
	Repo() = default;
	Repo(Repo& ot) = delete;
	virtual ~Repo() = default;

	virtual vector<Activitate>& getAll()=0;
	/*
		returneaza lista de elemente
	*/

	virtual bool exista(int id)=0;
	/*
		returneaza True daca activitatea cu id-ul dat se gaseste in lista
		sau False altfel
	*/

	virtual const Activitate& cauta(int id)=0;
	/*
		returneaza activitatea daca ea exista, altfel arunca exceptie
	*/

	virtual void stocheaza(const Activitate& act)=0;
	/*
		se adauga acitivatatea data ca param in lista
	*/

	virtual void modifica(const Activitate& act)=0;
	/*
		se modifica activitatea cu id-ul dat ca param
		cu activitatea data ca param
	*/

	virtual void sterge(int id)=0;
	/*
		se sterge activitatea cu id-ul dat ca param
	*/

	virtual void filtrare_descriere(vector<Activitate>& l_filtr, string descriere)=0;
	/*
		incarca in vectorul l_filtr activitatile care au descrierea data ca param
	*/

	virtual void filtrare_tip(vector<Activitate>& l_filtr, string tip)=0;
	/*
		incarca in vectorul l_filtr activitatile care au tipul dat ca param
	*/

	virtual void sortare(int tip_sort, int ord)=0;
	/*
		sorteaza lista de activitati dupa un anumit criteriu
	*/

	virtual const Activitate& cauta_titlu(string titlu)=0;
	/*
		returneaza activitatea cu titlul dat ca parametru
	*/

	virtual bool cauta_in_raport(unordered_map<string, int>& rap, string tip)=0;
	/*
		cauta in raportul dat ca parametru tipul dat
	*/

	virtual void raport(unordered_map<string, int>& rap)=0;
	/*
		genereaza un raport cu toate tipurile de activitati si frecventa fiecarui tip
	*/

};

class LabRepo :public Repo {
private:
	unordered_map<int,Activitate>elems;
	vector<Activitate>vect;
	double prob;

public:
	
	LabRepo() = default;
	//LabRepo(double prob) :prob{ prob } {

	//}
	LabRepo(LabRepo& ot) = delete;

	vector<Activitate>& getAll();
	/*
		returneaza lista de elemente
	*/

	//vector<Activitate> getAll();

	bool exista(int id) override;
	/*
		returneaza True daca activitatea cu id-ul dat se gaseste in lista
		sau False altfel
	*/

	const Activitate& cauta(int id) override;
	/*
		returneaza activitatea daca ea exista, altfel arunca exceptie
	*/

	void stocheaza(const Activitate& act) override;
	/*
		se adauga acitivatatea data ca param in lista
	*/

	void modifica(const Activitate& act) override;
	/*
		se modifica activitatea cu id-ul dat ca param
		cu activitatea data ca param
	*/

	void sterge(int id) override;
	/*
		se sterge activitatea cu id-ul dat ca param
	*/

	void filtrare_descriere(vector<Activitate>& l_filtr, string descriere) override;
	/*
		incarca in vectorul l_filtr activitatile care au descrierea data ca param
	*/

	void filtrare_tip(vector<Activitate>& l_filtr, string tip) override;
	/*
		incarca in vectorul l_filtr activitatile care au tipul dat ca param
	*/

	void sortare(int tip_sort, int ord) override;
	/*
		sorteaza lista de activitati dupa un anumit criteriu
	*/

	const Activitate& cauta_titlu(string titlu) override;
	/*
		returneaza activitatea cu titlul dat ca parametru
	*/

	bool cauta_in_raport(unordered_map<string, int>& rap, string tip) override;
	/*
		cauta in raportul dat ca parametru tipul dat
	*/

	void raport(unordered_map<string, int>& rap) override;
	/*
		genereaza un raport cu toate tipurile de activitati si frecventa fiecarui tip
	*/

};
class ActivitateRepository:public Repo{
private:

	vector<Activitate>elems;

public:

	ActivitateRepository(const ActivitateRepository& ot) = delete;

	ActivitateRepository() = default;

	virtual vector<Activitate>& getAll();
	/*
		returneaza lista de elemente
	*/

	virtual bool exista(int id);
	/*
		returneaza True daca activitatea cu id-ul dat se gaseste in lista
		sau False altfel
	*/

	virtual const Activitate& cauta(int id);
	/*
		returneaza activitatea daca ea exista, altfel arunca exceptie
	*/

	virtual void stocheaza(const Activitate& act);
	/*
		se adauga acitivatatea data ca param in lista
	*/

	virtual void modifica(const Activitate& act);
	/*
		se modifica activitatea cu id-ul dat ca param
		cu activitatea data ca param
	*/

	virtual void sterge(int id);
	/*
		se sterge activitatea cu id-ul dat ca param
	*/

	virtual void filtrare_descriere(vector<Activitate>& l_filtr, string descriere);
	/*
		incarca in vectorul l_filtr activitatile care au descrierea data ca param
	*/

	virtual void filtrare_tip(vector<Activitate>& l_filtr, string tip);
	/*
		incarca in vectorul l_filtr activitatile care au tipul dat ca param
	*/

	virtual void sortare(int tip_sort, int ord);
	/*
		sorteaza lista de activitati dupa un anumit criteriu
	*/

	virtual const Activitate& cauta_titlu(string titlu);
	/*
		returneaza activitatea cu titlul dat ca parametru
	*/

	virtual bool cauta_in_raport(unordered_map<string, int>& rap, string tip);
	/*
		cauta in raportul dat ca parametru tipul dat
	*/
	
	virtual void raport(unordered_map<string, int>& rap);
	/*
		genereaza un raport cu toate tipurile de activitati si frecventa fiecarui tip
	*/

};

class ActivitatiPlanificateRepository {
private:

	Repo& repo;
	vector<Activitate> act_planif;

public:

	ActivitatiPlanificateRepository(Repo& repo) :repo{ repo } {

	}

	ActivitatiPlanificateRepository(ActivitatiPlanificateRepository& ot) = delete;

	const vector<Activitate>& get_all();
	/*
		returneaza toate activitatile curente
	*/

	void delete_all();
	/*
		sterge toate activitatile curente
	*/

	void stocheaza(const Activitate& act);
	/*
		stocheaza activitatea data prin parametru in lista de activitati curente
	*/

	void generare_act_planif(int nr_activitati, vector<Activitate> activitati);
	/*
		se populeaza lista de activitati planificate cu un numar finit
		de activitati
	*/
};

class ActivitateFileRepository :public ActivitateRepository {
private:
	string file;
	void write_in_file();
	void read_from_file();
public:
	
	ActivitateFileRepository() = default;

	ActivitateFileRepository(string file) :file{ file } {
		read_from_file();
	}

	void stocheaza(const Activitate& act) override;
	/*
		stocheaza o activitate si in aplicatie si in fisier
	*/

	void modifica(const Activitate& act) override;
	/*
		modifica o activitate si in aplicatie si in fisier
	*/

	void sterge(int id) override;
	/*
		sterge o activitate si din aplicatie si din fisier
	*/

	void sortare(int tip_sort, int ord) override;
	/*
		sorteaza lista de activitati si in aplicatie si in fisier
	*/
};

class ExceptieRepository {
private:
	string msg;
public:
	ExceptieRepository(string msg) : msg{ msg } {
	}

	string get_msg();
	/*
		returneaza mesajul exceptiei
	*/

};

void test_repo();
/*
	se testeaza gestionarea listei
*/

void test_repo_file();
/*
	se testeaza gestionarea listei din fisiere
*/

void test_lab_repo();