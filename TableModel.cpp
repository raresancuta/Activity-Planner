#include "TableModel.h"

TableModel::TableModel(ActivitateController& ctr, QObject* parent) : QAbstractTableModel(parent), ctr(ctr) {
    activitati = ctr.get_all_act_planif();
}

int TableModel::rowCount(const QModelIndex& parent) const {
    return (int)activitati.size();
}

int TableModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return {};
    }

    const auto& act = activitati;
    const auto& activitate = act[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:return QString::number(activitate.get_id());
        case 1:return QString::fromStdString(activitate.get_titlu());
        case 2:return QString::fromStdString(activitate.get_descriere());
        case 3:return QString::fromStdString(activitate.get_tip());
        case 4:return QString::number(activitate.get_durata());
        default:return {};
        }
    }

    return {};
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:return "ID";
        case 1:return "Titlu";
        case 2:return "Descriere";
        case 3:return "Tip";
        case 4:return "Durata";
        default:return {};
        }
    }

    return {};
}

void TableModel::updateModel() {
    beginResetModel();
    endResetModel();
}

void TableModel::setRecords(std::vector<Activitate> rec) {
    activitati = std::move(rec);
    updateModel();
}

void TableModel::refreshModel() {
    activitati = ctr.get_all_act_planif();
    updateModel();
}