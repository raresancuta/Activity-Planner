#pragma once
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qtablewidget.h>
#include <QAbstractTableModel>
#include <qmessagebox.h>
#include <qpainter.h>

#include "TableModel.h"
#include "Observer.h"
#include "Controller.h"
#include "ListModel.h"

class ActivitateGUI: public QWidget {
public:
	ActivitateGUI(ActivitateController& ctr) : ctr{ ctr } {
		initGUI();
		model->refreshModel();
		initConnect();
	}
	
private:
	ActivitateController& ctr;

	QListView* list_view= new QListView(this);
	ListModel* model = new ListModel(ctr, this);

	QPushButton* sort_c_titlu = new QPushButton{ "&Sortare dupa titlu" };
	QPushButton* sort_c_descriere = new QPushButton{ "&Sortare dupa descriere" };
	QPushButton* add_button = new QPushButton{ "&Adauga" };
	QPushButton* modif_button = new QPushButton{ "&Modifica" };
	QPushButton* delete_button = new QPushButton{ "&Sterge" };
	QPushButton* undo_button = new QPushButton{ "&Undo" };
	QPushButton* filtr_tip_button = new QPushButton{ "&Filtrare" };
	QPushButton* filtr_descr_button = new QPushButton{ "&Filtrare" };

	QLineEdit* txt_id = new QLineEdit;
	QLineEdit* txt_titlu = new QLineEdit;
	QLineEdit* txt_descriere = new QLineEdit;
	QLineEdit* txt_tip = new QLineEdit;
	QLineEdit* txt_durata = new QLineEdit;
	
	QLineEdit* txt_cautare_titlu = new QLineEdit;
	QPushButton* cautare_button = new QPushButton{ "&Cauta" };

	QLineEdit* txt_filtr_tip = new QLineEdit;
	QLineEdit* txt_filtr_descr = new QLineEdit;

	QPushButton* reload_button = new QPushButton{ "&Reload" };

	void initGUI();
	/*
		initializeaza interfata grafica 
	*/

	void initConnect();
	/*
		se initializeaza conectarile
	*/

	bool val_int();
	/*
		validator pentru int-uri
	*/

	void adaugare_activitate();
	/*
		se adauga o activitate
	*/

	void modificare_activitate();
	/*
		se modifica o activitate
	*/

	void stergere_activitate();
	/*
		se sterge o activitate
	*/

	void cautare_activitate();
	/*
		se cauta o activitate
	*/

};

class PlanificareActivitatiGUI :public QWidget,public Observer {
public:

	PlanificareActivitatiGUI(ActivitateController& ctr) :ctr{ ctr } {
		initGUI();
		initConnect();
	}

private:

	ActivitateController& ctr;

	QTableView* table_view = new QTableView(this);
	TableModel* model = new TableModel(ctr, this);
	
	QPushButton* add_button = new QPushButton("Adaugare");
	QLineEdit* txt_add = new QLineEdit;
	QPushButton* generare_button = new QPushButton("Generare");
	QLineEdit* txt_generare = new QLineEdit;
	QPushButton* delete_list = new QPushButton("Goleste lista");

	QLineEdit* txt_fisier = new QLineEdit;
	QPushButton* save_csv_button = new QPushButton("Save to CSV");
	QPushButton* save_html_button = new QPushButton("Save to HTML");

	QPushButton* new_plan_act_obs = new QPushButton("Fereastra PlanifCRUD noua");
	QPushButton* new_plan_act_readOnly = new QPushButton("Fereastra PlanifReadOnly noua");
	void initGUI();
	/*
		initializeaza interfata grafica
	*/


	void initConnect();
	/*
		se initializeaza incarcarile
	*/

	void adaugare_activitate();
	/*
		se adauga o activitate
	*/

	void generare_activitati();
	/*
		se genereaza activitati
	*/

	void goleste_lista();
	/*
		se goleste lista cu activitati planificate
	*/

	void save_to_csv();
	/*
		salveaza lista de activitati planificate intr-un fisier CSV
	*/

	void save_to_html();
	/*
		salveaza lista de activitati planificate intr-un fisier HTML
	*/

	void update() override;
};

class PlanificareActivitatiObs :public QWidget,public Observer {
public:

	PlanificareActivitatiObs(ActivitateController& ctr) :ctr{ ctr } {
		initGUI();
		initConnect();
		model->refreshModel();
	}

	ActivitateController& ctr;

	QTableView* table_view = new QTableView(this);
	TableModel* model = new TableModel(ctr, this);

	QPushButton* add_button = new QPushButton("Adaugare");
	QLineEdit* txt_add = new QLineEdit;
	QPushButton* generare_button = new QPushButton("Generare");
	QLineEdit* txt_generare = new QLineEdit;
	QPushButton* delete_list = new QPushButton("Goleste lista");
	

	void initGUI();
	/*
		initializeaza interfata grafica
	*/


	void initConnect();
	/*
		se initializeaza incarcarile
	*/

	void adaugare_activitate();
	/*
		se adauga o activitate
	*/

	void generare_activitati();
	/*
		se genereaza activitati
	*/

	void goleste_lista();
	/*
		se goleste lista cu activitati planificate
	*/

	void update() override;
	

};

class PlanificareActivitatiRDONLY :public QWidget, public Observer {
private:
	ActivitateController& ctr;
public:
	PlanificareActivitatiRDONLY(ActivitateController& ctr) :ctr{ ctr } {
		ctr.addObserver(this);
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override;

	void update() override;

};

