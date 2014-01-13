#ifndef FINISHEDEXAM_H
#define FINISHEDEXAM_H

#include <enumerations.h>
#include <QString>
#include <QList>

class FinishedExam
{
    QString _candidateID;
    GroupID _groupID;
    QList<AnswerID> _answers;
    double _points;
    bool _valid;
public:
    FinishedExam();
    FinishedExam(QString candidateID, GroupID groupID, QList<AnswerID> answers);
    QString candidateID() const;
    void setCandidateID(const QString &candidateID);
    GroupID groupID() const;
    void setGroupID(const GroupID &groupID);
    QList<AnswerID> answers() const;
    void setAnswers(const QList<AnswerID> &answers);
    double points() const;
    void setPoints(double points);
    bool valid() const;
    void setValid(bool valid);
};

#endif // FINISHEDEXAM_H
