#include "testmodel.h"

#include <QXmlStreamWriter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>

TestModel::TestModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    //    data_ += Student();
    data_.resize(3);
}

//QVariant TestModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//bool TestModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}


int TestModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return data_.count();
    }
    return data_.count();
}

int TestModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 3;
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case 0:
                return data_[index.row()].name_;
            case 1:
                return data_[index.row()].lastName_;
            case 2:
                return data_[index.row()].marks_["YaMP"];
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            default:
                break;
            }
        }
    }

    return QVariant();
}

bool TestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::EditRole) {
            switch (index.column()) {
            case 0:
                data_[index.row()].name_ = (value.toString());
                break;
            case 1:
                data_[index.row()].lastName_ = (value.toString());
                break;
            case 2:
                data_[index.row()].marks_["YaMP"] = (value.toInt());
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            default:
                break; }
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TestModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index); // FIXME: Implement me!
}

bool TestModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool TestModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

bool TestModel::writeToXML(QIODevice *device)
{
    QXmlStreamWriter xml;

    xml.setDevice(device);

    xml.writeStartDocument();
    for(auto el : data_) {
        xml.writeStartElement("Student");
        xml.writeAttribute("name", el.name_);
        xml.writeAttribute("lastname", el.lastName_);
        for(auto mark : el.marks_){
            xml.writeTextElement("YaMP", QString::number(mark));
        }

        xml.writeEndElement();
    }

    xml.writeEndDocument();
    return true;
}

bool TestModel::readFromXML(QIODevice *device)
{
    beginResetModel();
    data_.clear();

    QXmlStreamReader xml;
    xml.setDevice(device);

    Student student;
    xml.readNextStartElement();
    qDebug() << xml.name() ;
    while (!xml.atEnd()) {
        xml.readNextStartElement();
        qDebug() << xml.name() ;
        if (xml.name() == QLatin1String("Student")){
            student.name_ = xml.attributes().value("name").toString();
            student.lastName_ = xml.attributes().value("lastname").toString();
            xml.readNextStartElement();
            qDebug() << xml.name() ;
            if (xml.name() == QLatin1String("YaMP")){
                auto str = xml.readElementText();
                student.marks_["YaMP"] = str.toInt();

                data_ += student;
            }
            xml.skipCurrentElement();
        } else {
            xml.skipCurrentElement();
        }
        qDebug() << "XML end :" << xml.atEnd();
    }
//    xml.skipCurrentElement();

    endResetModel();
    qDebug() << " Error " << xml.error();
    qDebug() << " Error " << xml.errorString();
    return !xml.error();
}

void TestModel::writeToJSON(QIODevice *device)
{
    QJsonArray students;

    for(auto el : data_) {
        QJsonObject student;
        student["name"] = el.name_;
        student["lastname"] = el.lastName_;
        QJsonArray marks;
        for(auto mark : el.marks_){
            QJsonObject val;
            val["YaMP"] = QString::number(mark);
            marks.push_back(val);
        }
        student["marks"] = marks;
        students.push_back(student);
    }

    QJsonDocument doc(students);

    device->write(doc.toJson());
    return;
}

bool TestModel::readFromJSON(QString val)
{

    beginResetModel();
    data_.clear();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonArray students = doc.array();

    for(auto el : students) {
        auto obj = el.toObject();
        qDebug() << obj;

        Student student;
        student.name_ = obj["name"].toString();
        student.lastName_ = obj["lastname"].toString();

        auto marks = obj["marks"].toArray();
        for(auto m : marks) {
            auto mark = m.toObject();
            student.marks_["YaMP"] = mark["YaMP"].toString().toInt();
        }

//        student.name_ = el.
        data_ += student;
    }



    endResetModel();

//    qDebug() << val;
//    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
//    QJsonObject sett2 = doc.object();
//    QJsonValue value = sett2.value(QString("appName"));
//    qWarning() << value;
//    QJsonObject item = value.toObject();
//    qWarning() << tr("QJsonObject of description: ") << item;

//    /* in case of string value get value and convert into string*/
//    qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
//    QJsonValue subobj = item["description"];
//    qWarning() << subobj.toString();

//    /* in case of array get array and convert into string*/
//    qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
//    QJsonArray test = item["imp"].toArray();
//    qWarning() << test[1].toString();
    return true;
}

