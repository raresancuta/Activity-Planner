#pragma once

#include <QAbstractListModel>
#include "Controller.h"

class ListModel : public QAbstractListModel {
private:
    ActivitateController& ctr;
    std::vector<Activitate> activitati;

public:
    explicit ListModel(ActivitateController& ctr, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void updateModel();
    void setRecords(std::vector<Activitate> rec);
    void refreshModel();

};