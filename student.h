#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QMap>

class Student
{
public:
    Student();
    Student(QString n, QString l, QMap<QString, int> m);

    QString name_;
    QString lastName_;

    QMap<QString, int> marks_;
};

#endif // STUDENT_H
