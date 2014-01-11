#ifndef FINISHEDEXAM_H
#define FINISHEDEXAM_H

#include <enumerations.h>
#include <QString>
#include <QList>

class FinishedExam
{
    QString _personID;
    QString _candidateID;
    GroupID _groupID;
    QList<AnswerID> _answers;
    double _points;
public:
    FinishedExam();
    FinishedExam(QString personID, QString candidateID, GroupID groupID, QList<AnswerID> answers);


    QString personID() const;
    void setPersonID(const QString &personID);
    QString candidateID() const;
    void setCandidateID(const QString &candidateID);
    GroupID groupID() const;
    void setGroupID(const GroupID &groupID);
    QList<AnswerID> answers() const;
    void setAnswers(const QList<AnswerID> &answers);
    double points() const;
    void setPoints(double points);
};

#endif // FINISHEDEXAM_H
