#include "ListModel.h"

ListModel::ListModel(ActivitateController& ctr, QObject* parent) : QAbstractListModel(parent), ctr(ctr) {
    activitati = ctr.getAll();
}

int ListModel::rowCount(const QModelIndex& parent) const {
    return (int)activitati.size();
}

QVariant ListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= activitati.size()) {
        return {};
    }

    const auto& act = activitati[index.row()];

    if (role == Qt::DisplayRole) {
        return QString::fromStdString(act.get_titlu());
    }

    return {};
}

void ListModel::updateModel() {
    beginResetModel();
    endResetModel();
}

void ListModel::setRecords(std::vector<Activitate> rec) {
    activitati = std::move(rec);
    updateModel();
}

void ListModel::refreshModel() {
    activitati = ctr.getAll();
    updateModel();
}
