#include "Console.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void ActivitateConsole::print_menu() {
	cout << endl << "Meniu :" << endl;
	cout << "1. Afisare lista" << endl << "2. Adaugare activitate" << endl;
	cout << "3. Modificare activitate" << endl << "4. Stergere activitate" << endl;
	cout << "5. Cautare activitate" << endl << "6. Filtrare activitate" << endl;
	cout << "7. Sortare activitati" << endl << "8. Golire lista activitati planificate" << endl;
	cout << "9. Adaugare activitate in lista de activitati planificate" << endl << "10. Generare activitati planificate" << endl;
	cout << "11. Salvare lista activitati planificate" <<endl<<"12. Raport cu tipuri de activitati"<< endl;
	cout << "13. Undo" << endl << "14. Exit" << endl;
}

void ActivitateConsole::print_lista() {
	cout << endl << "Lista activitatilor : " << endl << endl;
	auto& activitati = ctr.getAll();
	for (const Activitate& act : activitati)
		cout << act.get_id() << "\t" << act.get_titlu() << "\t" << act.get_descriere() << "\t" << act.get_tip() << "\t" << act.get_durata() << endl;
	cout << endl;
}

void ActivitateConsole::adaugare() {
	string titlu, descriere, tip;
	string id, durata;

	cout << "Introduceti ID-ul activitatii: ";
	cin >> id;
	cout << "Introduceti titlul activitatii : ";
	cin >> titlu;
	cout << "Introduceti descrierea activitatii : ";
	cin >> descriere;
	cout << "Introduceti tipul activitatii : ";
	cin >> tip;
	cout << "Introduceti durata activitatii : ";
	cin >> durata;

	int id_int = -1, durata_int = -1;
	bool ok = false;
	try {
		id_int = stoi(id);
	}
	catch (std::invalid_argument) {
		cout << endl << "ID invalid" << endl;
		ok = true;
	}
	try {
		durata_int = stoi(durata);
	}
	catch (std::invalid_argument) {
		cout << endl << "Durata invalida" << endl;
		ok = true;
	}

	if (!ok) {
		try {
			ctr.adauga(id_int, titlu, descriere, tip, durata_int);
			cout << endl << "Adaugare efectuata cu succes!" << endl;
		}
		catch (ExceptieRepository& ot) {
			cout << endl << ot.get_msg() << endl;
		}
		catch (ValidatorException& ot) {
			vector<string>& erori = ot.get_erori();
			for (auto& eroare : erori) {
				cout << endl << eroare << endl;
			}
		}
	}
	print_lista();
}

void ActivitateConsole::modificare() {
	string titlu, descriere, tip;
	string id, durata;

	cout << endl << "Introduceti ID-ul activitatii : ";
	cin >> id;
	cout << "Introduceti titlul activitatii : ";
	cin >> titlu;
	cout << "Introduceti descrierea activitatii : ";
	cin >> descriere;
	cout << "Introduceti tipul activitatii : ";
	cin >> tip;
	cout << "Introduceti durata activitatii : ";
	cin >> durata;

	int id_int = -1, durata_int = -1;
	bool ok = false;
	try {
		id_int = stoi(id);
	}
	catch (std::invalid_argument) {
		cout << endl << "ID invalid" << endl;
		ok = true;
	}
	try {
		durata_int = stoi(durata);
	}
	catch (std::invalid_argument) {
		cout << endl << "Durata invalida" << endl;
		ok = true;
	}

	if (!ok) {
		try {
			ctr.modifica(id_int, titlu, descriere, tip, durata_int);
			cout << endl << "Modificare efectuata cu succes!" << endl;
		}
		catch (ExceptieRepository& ot) {
			cout << endl << ot.get_msg() << endl;
		}
		catch (ValidatorException& ot) {
			vector<string>& erori = ot.get_erori();
			for (auto& eroare : erori) {
				cout << endl << eroare << endl;
			}
		}
	}
	print_lista();
}

void ActivitateConsole::stergere() {
	int id;

	cout << endl << "Introduceti ID-ul activitatii : ";
	cin >> id;
	try {
		ctr.sterge(id);
		cout << endl << "Stergere efectuata cu succes!" << endl;
	}
	catch (ExceptieRepository& ot) {
		cout << endl << ot.get_msg() << endl;
	}
	print_lista();
}

void ActivitateConsole::cautare() {
	int id;

	cout << endl << "Introduceti ID-ul activitatii : ";
	cin >> id;
	try {
		const Activitate& act = ctr.cauta(id);
		cout << endl << "Activitatea cautata este : " << endl;
		cout << act.get_id() << "\t" << act.get_titlu() << "\t" << act.get_descriere() << "\t" << act.get_tip() << "\t" << act.get_durata() << endl;
	}
	catch (ExceptieRepository& ot) {
		cout << endl << ot.get_msg() << endl;
	}
	cout << endl;
	print_lista();
}

void ActivitateConsole::filtrare() {
	int tip_filtru;
	string filtru;

	cout << "1. Filtru dupa descriere" << endl << "2. Filtru dupa tip" << endl;
	cout << "Introduceti optiunea : ";
	cin >> tip_filtru;
	if (tip_filtru == 1) {
		cout << endl << "Introduceti descrierea : ";
		cin >> filtru;
		vector<Activitate> l_filtr;
		ctr.filtreaza(l_filtr, 1, filtru);
		cout << endl << "Activitatile cu descrierea data sunt" << endl;
		for (const Activitate& act : l_filtr) {
			cout << act.get_id() << "\t" << act.get_titlu() << "\t" << act.get_descriere() << "\t" << act.get_tip() << "\t" << act.get_durata() << endl;

		}
		cout << endl;
	}
	else if (tip_filtru == 2) {
		cout << endl << "Introduceti tipul : ";
		cin >> filtru;
		vector<Activitate> l_filtr;
		ctr.filtreaza(l_filtr, 2, filtru);
		cout << endl << "Activitatile cu tipul dat sunt" << endl;
		for (const Activitate& act : l_filtr) {
			cout << act.get_id() << "\t" << act.get_titlu() << "\t" << act.get_descriere() << "\t" << act.get_tip() << "\t" << act.get_durata() << endl;
		}
		cout << endl;
	}
	else cout << "Comanda invalida" << endl;

}

void ActivitateConsole::sortare() {
	int cmd;
	cout << "1. Crescator dupa titlu" << endl << "2. Crescator dupa descriere" << endl;
	cout << "3. Crescator dupa tip si durata" << endl << "4. Descrescator dupa titlu" << endl;
	cout << "5. Descrescator dupa descriere" << endl << "6. Descrescator dupa tip si durata" << endl;
	cout << "Introduceti optiunea : ";
	cin >> cmd;
	switch (cmd) {
	case 1:
		ctr.sortare(1, 1);
		break;
	case 2:
		ctr.sortare(2, 1);
		break;
	case 3:
		ctr.sortare(3, 1);
		break;
	case 4:
		ctr.sortare(1, 2);
		break;
	case 5:
		ctr.sortare(2, 2);
		break;
	case 6:
		ctr.sortare(3, 2);
		break;
	default:
		cout << "Comanda invalida!" << endl;
		break;
	}
	print_lista();
}
void ActivitateConsole::print_lista_act_planif() {
	cout << endl << "Lista activitatilor planificate : " << endl << endl;
	const auto& act_planif = ctr.get_all_act_planif();
	for (const auto& act : act_planif) 
		cout << act.get_id() << "\t" << act.get_titlu() << "\t" << act.get_descriere() << "\t" << act.get_tip() << "\t" << act.get_durata() << endl;
	cout << endl;
}
void ActivitateConsole::golire_act_planif() {
	ctr.delete_act_planif();
	print_lista_act_planif();
}

void ActivitateConsole::adaugare_act_planif() {
	string titlu;
	cout << "Introduceti titlul activitatii : ";
	cin >> titlu;
	try {
		ctr.adauga_act_planif(titlu);
	}
	catch (ExceptieRepository& ot) {
		cout << endl << ot.get_msg() << endl;
	}
	print_lista_act_planif();
}

void ActivitateConsole::generare_act_planif() {
	int nr_activitati;
	cout << "Introduceti numarul de activitati ce doriti a fi generate : ";
	cin >> nr_activitati;
	try{
		ctr.generare_act_random(nr_activitati);
	}
	catch (ExceptieRepository& ot) {
		cout << endl << ot.get_msg() << endl;
	}
	print_lista_act_planif();
}

void ActivitateConsole::salvare_fisier() {
	int cmd;
	cout << "1. Salvare in fisier CSV" << endl << "2. Salvare in fisier HTML" << endl << "Introduceti optiunea :";
	cin >> cmd;
	if (cmd == 1) {
		string fisier;
		cout << "Introduceti numele fisierului : ";
		cin >> fisier;
		ctr.save_to_csv(fisier);
	}
	else if (cmd == 2) {
		string fisier;
		cout << "Introduceti numele fisierului : ";
		cin >> fisier;
		ctr.save_to_html(fisier);
	}
	print_lista_act_planif();
}

void ActivitateConsole::raport() {
	unordered_map<string, int> raport;
	ctr.raport(raport);
	for (auto& x : raport) {
		cout << endl << x.first << "\t" << x.second << endl;
	}
}

void ActivitateConsole::undo() {
	try {
		ctr.undo();
	}
	catch (std::exception& ot) {
		cout << endl << ot.what() << endl;
	}
	print_lista();
}
void ActivitateConsole::run() {
	while (true) {
		print_menu();
		int cmd;
		cout << "Introduceti optiunea : ";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			print_lista();
			break;
		case 2:
			adaugare();
			break;
		case 3:
			modificare();
			break;
		case 4:
			stergere();
			break;
		case 5:
			cautare();
			break;
		case 6:
			filtrare();
			break;
		case 7:
			sortare();
			break;
		case 8:
			golire_act_planif();
			break;
		case 9:
			adaugare_act_planif();
			break;
		case 10:
			generare_act_planif();
			break;
		case 11:
			salvare_fisier();
			break;
		case 12:
			raport();
			break;
		case 13:
			undo();
			break;
		case 14:
			exit(0);
		default:
			cout << endl << "Comanda Invalida !" << endl;
			break;
		}
	}
}