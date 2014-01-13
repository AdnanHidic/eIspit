#include "exam.h"

Exam::Exam()
{
}

Exam::Exam(QString name, QList<ExamGroup> examgroups):
    _name(name), _examgroups(examgroups)
{

}

QString Exam::name() const
{
    return _name;
}

void Exam::setName(const QString &name)
{
    _name = name;
}

QList<ExamGroup> Exam::examgroups() const
{
    return _examgroups;
}

void Exam::setExamgroups(QList<ExamGroup> examgroups)
{
    _examgroups = examgroups;
}

