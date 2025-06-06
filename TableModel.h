#include <QAbstractTableModel>
#include "Controller.h"

class TableModel : public QAbstractTableModel {
private:
    ActivitateController& ctr;
    std::vector<Activitate> activitati;

public:
    explicit TableModel(ActivitateController& ctr, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateModel();
    void setRecords(std::vector<Activitate> rec);
    void refreshModel();
};