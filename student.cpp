#include "student.h"

Student::Student():
    name_("Name"), lastName_("Surename")
{
    marks_["YaMP"] = 4;
}

Student::Student(QString n, QString l, QMap<QString, int> m)
    :name_(n), lastName_(l), marks_(m)
{ }
