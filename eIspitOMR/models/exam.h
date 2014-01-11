#ifndef EXAM_H
#define EXAM_H

#include <QList>
#include <QString>
#include <examgroup.h>

class Exam
{
    QString _name;
    QList<ExamGroup> _examgroups;
public:
    Exam();
    Exam(QString name, QList<ExamGroup> examgroups);


    QString name() const;
    void setName(const QString &name);
    QList<ExamGroup> examgroups() const;
    void setExamgroups(const QList<ExamGroup> &examgroups);
};

#endif // EXAM_H
