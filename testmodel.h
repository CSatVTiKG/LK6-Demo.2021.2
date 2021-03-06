#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QIODevice>

#include "student.h"

class TestModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TestModel(QObject *parent = nullptr);

    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
//    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;



    bool writeToXML(QIODevice *device);
    bool readFromXML(QIODevice *device);

    void writeToJSON(QIODevice *device);
    bool readFromJSON(QString str);



private:
    QVector<Student> data_;

};

#endif // TESTMODEL_H
