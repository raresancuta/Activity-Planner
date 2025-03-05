#include "PlanifActivitatiGUI.h"

void ActivitateGUI::initGUI() {
    QHBoxLayout* lyMain = new QHBoxLayout{};
    setLayout(lyMain);
   
    QVBoxLayout* lyList = new QVBoxLayout{};

    list_view->setModel(model);
    lyList->addWidget(list_view);

    QHBoxLayout* lyFiltrDescr = new QHBoxLayout;
    lyFiltrDescr->addWidget(new QLabel("Descriere : "));
    lyFiltrDescr->addWidget(txt_filtr_descr);
    lyFiltrDescr->addWidget(filtr_descr_button);
    lyList->addLayout(lyFiltrDescr);

    QHBoxLayout* lyFiltrTitlu = new QHBoxLayout;
    lyFiltrTitlu->addWidget(new QLabel("Tip : "));
    lyFiltrTitlu->addWidget(txt_filtr_tip);
    lyFiltrTitlu->addWidget(filtr_tip_button);
    lyList->addLayout(lyFiltrTitlu);
    lyList->addWidget(reload_button);

    QHBoxLayout* lySortButtons = new QHBoxLayout{};
    lySortButtons->addWidget(sort_c_titlu);
    lySortButtons->addWidget(sort_c_descriere);
    lyList->addLayout(lySortButtons);

    lyMain->addLayout(lyList);

    QVBoxLayout* lyOperations = new QVBoxLayout;
    auto form_act = new QFormLayout;
    form_act->addRow("ID", txt_id);
    form_act->addRow("Titlu", txt_titlu);
    form_act->addRow("Descriere", txt_descriere);
    form_act->addRow("Tip", txt_tip);
    form_act->addRow("Durata", txt_durata);
    lyOperations->addLayout(form_act);

    auto lyBtn = new QHBoxLayout;
    lyBtn->addWidget(add_button);
    lyBtn->addWidget(modif_button);
    lyBtn->addWidget(delete_button);
    lyBtn->addWidget(undo_button);
    lyOperations->addLayout(lyBtn);

    QHBoxLayout* ly_cautare = new QHBoxLayout;
    
    ly_cautare->addWidget(new QLabel("Titlu : "));
    ly_cautare->addWidget(txt_cautare_titlu);
    ly_cautare->addWidget(cautare_button);
    lyOperations->addLayout(ly_cautare);

    /*QVBoxLayout* ly_rap = new QVBoxLayout;

    unordered_map<string, int> rap;
    ctr.raport(rap);
    unordered_map<string, int>::iterator it = rap.begin();
    for (int i = 0; i < rap.size(); i++) {
        string tip = it->first;
        QPushButton* btnTip = new QPushButton(QString::fromStdString(tip));
        ly_rap->addWidget(btnTip);
        QObject::connect(btnTip, &QPushButton::clicked, [this,tip]() {
            vector<Activitate>l_filtr;
            ctr.filtreaza(l_filtr, 2, tip);
            int size = l_filtr.size();
            QMessageBox::information(this, "Info", QString::number(size));
            });
        ++it;
    }
    lyOperations->addLayout(ly_rap);*/
    lyMain->addLayout(lyOperations);
}



bool ActivitateGUI::val_int() {
    bool ok;
    txt_id->text().QString::toInt(&ok);
    if (ok == 0) {
        QMessageBox::warning(nullptr, "EROARE", "ID invalid");
        return false;
    }
    txt_durata->text().QString::toInt(&ok);
    if (ok == 0) {
        QMessageBox::warning(nullptr, "EROARE", "Durata invalida");
        return false;
    }
    return true;
}

void ActivitateGUI::initConnect() {
    QObject::connect(add_button, &QPushButton::clicked, this, &ActivitateGUI::adaugare_activitate);
    QObject::connect(list_view->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        if (list_view->selectionModel()->selectedIndexes().isEmpty()) {
            txt_id->setText("");
            txt_titlu->setText("");
            txt_descriere->setText("");
            txt_tip->setText("");
            txt_durata->setText("");
            return;
        }
        auto select_act_index = list_view->selectionModel()->selectedIndexes().at(0);
        QString titlu = select_act_index.data(Qt::DisplayRole).toString();
        const Activitate& act = ctr.cauta_titlu(titlu.QString::toStdString());
        txt_id->setText(QString::number(act.get_id()));
        txt_titlu->setText(titlu);
        txt_descriere->setText(QString::fromStdString(act.get_descriere()));
        txt_tip->setText(QString::fromStdString(act.get_tip()));
        txt_durata->setText(QString::number(act.get_durata()));
        });
    QObject::connect(modif_button, &QPushButton::clicked, this, &ActivitateGUI::modificare_activitate);
    QObject::connect(delete_button, &QPushButton::clicked, this, &ActivitateGUI::stergere_activitate);
    QObject::connect(cautare_button, &QPushButton::clicked, this, &ActivitateGUI::cautare_activitate);
    QObject::connect(sort_c_titlu, &QPushButton::clicked, [&]() {
        ctr.sortare(1, 1);
        model->refreshModel();
        });
    QObject::connect(sort_c_descriere, &QPushButton::clicked, [&]() {
        ctr.sortare(2, 1);
        model->refreshModel();
        });
    QObject::connect(undo_button, &QPushButton::clicked, [&]() {
        try {
            ctr.undo();
            model->refreshModel();
        }
        catch (std::exception &ot) {
            QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.what()));
        }
        });
    /*QObject::connect(filtr_tip_button, &QPushButton::clicked, [&]() {
        lista_act->clear();
        vector<Activitate> l_filtr;
        auto filtru = txt_filtr_tip->text();
        ctr.filtreaza(l_filtr, 2, filtru.QString::toStdString());
        for (const auto& act : l_filtr) {
            lista_act->addItem(QString::fromStdString(act.get_titlu()));
        }
        });
    QObject::connect(filtr_descr_button, &QPushButton::clicked, [&]() {
        lista_act->clear();
        vector<Activitate> l_filtr;
        auto filtru = txt_filtr_descr->text();
        ctr.filtreaza(l_filtr, 1, filtru.QString::toStdString());
        for (const auto& act : l_filtr) {
            lista_act->addItem(QString::fromStdString(act.get_titlu()));
        }
        });*/
    QObject::connect(reload_button, &QPushButton::clicked, [&]() {
        model->refreshModel();
        });
}
void ActivitateGUI::adaugare_activitate() {
    auto id = txt_id->text();
    auto titlu = txt_titlu->text();
    auto descriere = txt_descriere->text();
    auto tip = txt_tip->text();
    auto durata = txt_durata->text();
    if (val_int()) {
        try {
            ctr.adauga(id.QString::toInt(), titlu.QString::toStdString(), descriere.QString::toStdString(), tip.QString::toStdString(), durata.QString::toInt());
            model->refreshModel();
        }
        catch (ValidatorException& ot) {
            vector<string>& erori = ot.get_erori();
            QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(erori[0]));
        }
        catch (ExceptieRepository& ot) {
            QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
        }
    }
}

void ActivitateGUI::modificare_activitate() {
    auto id = txt_id->text();
    auto titlu = txt_titlu->text();
    auto descriere = txt_descriere->text();
    auto tip = txt_tip->text();
    auto durata = txt_durata->text();
    if (val_int()) {
        try {
            ctr.modifica(id.QString::toInt(), titlu.QString::toStdString(), descriere.QString::toStdString(), tip.QString::toStdString(), durata.QString::toInt());
            model->refreshModel();
        }
        catch (ValidatorException& ot) {
            vector<string>& erori = ot.get_erori();
            QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(erori[0]));
        }
        catch (ExceptieRepository& ot) {
            QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
        }
    }
}

void ActivitateGUI::stergere_activitate() {
    auto id = txt_id->text();
    if (val_int()) {
        try {
            ctr.sterge(id.QString::toInt());
            model->refreshModel();
        }
        catch (ExceptieRepository& ot) {
            QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
        }
    }
}

void ActivitateGUI::cautare_activitate() {
    try {
        const Activitate& act = ctr.cauta_titlu(txt_cautare_titlu->text().QString::toStdString());
        txt_id->setText(QString::number(act.get_id()));
        txt_titlu->setText(txt_cautare_titlu->text());
        txt_descriere->setText(QString::fromStdString(act.get_descriere()));
        txt_tip->setText(QString::fromStdString(act.get_tip()));
        txt_durata->setText(QString::number(act.get_durata()));
    }
    catch (ExceptieRepository& ot) {
        QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
    }
}

void PlanificareActivitatiGUI::initGUI() {

    QHBoxLayout* lyMain = new QHBoxLayout;
    setLayout(lyMain);

    table_view->setModel(model);
    table_view->setMinimumWidth(400);
    lyMain->addWidget(table_view);

    QVBoxLayout* lyOperations = new QVBoxLayout;

    QHBoxLayout* lyAdd = new QHBoxLayout;
    lyAdd->addWidget(new QLabel("Titlu : "));
    lyAdd->addWidget(txt_add);
    lyAdd->addWidget(add_button);
    lyOperations->addLayout(lyAdd);

    auto lyGenerare = new QHBoxLayout;
    lyGenerare->addWidget(new QLabel("Nr de activitati :"));
    lyGenerare->addWidget(txt_generare);
    lyGenerare->addWidget(generare_button);
    lyOperations->addLayout(lyGenerare);

    lyOperations->addWidget(delete_list);

    auto lySave = new QHBoxLayout;
    lySave->addWidget(new QLabel("Nume fisier : "));
    lySave->addWidget(txt_fisier);
    lyOperations->addLayout(lySave);

    auto lySaveButtons = new QHBoxLayout;
    lySaveButtons->addWidget(save_csv_button);
    lySaveButtons->addWidget(save_html_button);
    lyOperations->addLayout(lySaveButtons);
    lyOperations->addWidget(new_plan_act_obs);
    lyOperations->addWidget(new_plan_act_readOnly);
    lyMain->addLayout(lyOperations);

}
void PlanificareActivitatiGUI::initConnect() {
    ctr.addObserver(this);
    QObject::connect(add_button, &QPushButton::clicked, this, &PlanificareActivitatiGUI::adaugare_activitate);
    QObject::connect(delete_list, &QPushButton::clicked, this, &PlanificareActivitatiGUI::goleste_lista);
    QObject::connect(generare_button, &QPushButton::clicked, this, &PlanificareActivitatiGUI::generare_activitati);
    QObject::connect(save_csv_button, &QPushButton::clicked, this, &PlanificareActivitatiGUI::save_to_csv);
    QObject::connect(save_html_button, &QPushButton::clicked, this, &PlanificareActivitatiGUI::save_to_html);
    QObject::connect(new_plan_act_obs, &QPushButton::clicked, [&]() {
        auto new_window = new PlanificareActivitatiObs{ ctr };
        new_window->show();
        });
    QObject::connect(new_plan_act_readOnly, &QPushButton::clicked, [&]() {
        auto new_window = new PlanificareActivitatiRDONLY{ ctr };
        new_window->show();
        });
}
void PlanificareActivitatiGUI::update() {
    model->refreshModel();
}

void PlanificareActivitatiObs::update() {
    model->refreshModel();
}
void PlanificareActivitatiGUI::adaugare_activitate() {
    auto titlu = txt_add->text();
    try {
        ctr.adauga_act_planif(titlu.QString::toStdString());
        model->refreshModel();
    }
    catch (ExceptieRepository& ot) {
        QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
    }
}

void PlanificareActivitatiGUI::goleste_lista() {
    ctr.delete_act_planif();
    model->refreshModel();
}

void PlanificareActivitatiGUI::generare_activitati() {
    auto nr_act = txt_generare->text();

    try {
        ctr.generare_act_random(nr_act.QString::toInt());
        model->refreshModel();
    }
    catch (ExceptieRepository& ot) {
        QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
    }
}

void PlanificareActivitatiGUI::save_to_csv() {
    auto fisier = txt_fisier->text();
    ctr.save_to_csv(fisier.QString::toStdString());
}

void PlanificareActivitatiGUI::save_to_html() {
    auto fisier = txt_fisier->text();
    ctr.save_to_html(fisier.QString::toStdString());
}

// Observer 

void PlanificareActivitatiObs::initConnect() {
    ctr.addObserver(this);
    QObject::connect(add_button, &QPushButton::clicked, this, &PlanificareActivitatiObs::adaugare_activitate);
    QObject::connect(delete_list, &QPushButton::clicked, this, &PlanificareActivitatiObs::goleste_lista);
    QObject::connect(generare_button, &QPushButton::clicked, this, &PlanificareActivitatiObs::generare_activitati);
}

void PlanificareActivitatiObs::adaugare_activitate(){
    auto titlu = txt_add->text();
    try {
        ctr.adauga_act_planif(titlu.QString::toStdString());
        model->refreshModel();
    }
    catch (ExceptieRepository& ot) {
        QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
    }
}

void PlanificareActivitatiObs::goleste_lista() {
    ctr.delete_act_planif();
    model->refreshModel();
}

void PlanificareActivitatiObs::generare_activitati() {
    auto nr_act = txt_generare->text();

    try {
        ctr.generare_act_random(nr_act.QString::toInt());
        model->refreshModel();
    }
    catch (ExceptieRepository& ot) {
        QMessageBox::warning(nullptr, "EROARE", QString::fromStdString(ot.get_msg()));
    }
}


void PlanificareActivitatiObs::initGUI() {

    QHBoxLayout* lyMain = new QHBoxLayout;
    setLayout(lyMain);

    table_view->setModel(model);
    table_view->setMinimumWidth(400);
    lyMain->addWidget(table_view);

    QVBoxLayout* lyOperations = new QVBoxLayout;

    QHBoxLayout* lyAdd = new QHBoxLayout;
    lyAdd->addWidget(new QLabel("Titlu : "));
    lyAdd->addWidget(txt_add);
    lyAdd->addWidget(add_button);
    lyOperations->addLayout(lyAdd);

    auto lyGenerare = new QHBoxLayout;
    lyGenerare->addWidget(new QLabel("Nr de activitati :"));
    lyGenerare->addWidget(txt_generare);
    lyGenerare->addWidget(generare_button);
    lyOperations->addLayout(lyGenerare);

    lyOperations->addWidget(delete_list);
    
    lyMain->addLayout(lyOperations);

}

void PlanificareActivitatiRDONLY::paintEvent(QPaintEvent* ev) {
    QPainter p{ this };
    int x = 10;
    for (const auto& u : ctr.get_all_act_planif()) {
        p.drawRect(x, 0, 20, ctr.get_all_act_planif().size() * 10);
        x += 40;
    }
}

void PlanificareActivitatiRDONLY::update() {
    repaint();
}