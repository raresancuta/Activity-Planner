#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include "Console.h"
#include "PlanifActivitatiGUI.h"

int main(int argc, char *argv[])
{
    test_activitate();
    test_repo();
    test_lab_repo();
    test_repo_file();
    test_ctr();
    Validator val;
    //ActivitateRepository repo;
    ActivitateFileRepository repo{ "activitati.txt" };
    //LabRepo repo;
    ActivitatiPlanificateRepository act_planif{ repo };
    ActivitateController ctr{ repo,act_planif,val };
    //ActivitateConsole cons{ ctr };
    QApplication a(argc, argv);
    ActivitateGUI gui{ctr};
    PlanificareActivitatiGUI gui_act_planif{ctr};
    
    gui.show();
    gui_act_planif.show();

    return a.exec();
}
