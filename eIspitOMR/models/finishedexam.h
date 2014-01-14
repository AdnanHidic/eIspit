#ifndef FINISHEDEXAM_H
#define FINISHEDEXAM_H

#include <enumerations.h>
#include <QString>
#include <QVector>

class FinishedExam
{
    QString _candidateID;
    GroupID _groupID;
    QVector<AnswerID> _answers;
    double _points;
    bool _valid;
public:
    FinishedExam();
    FinishedExam(QString candidateID, GroupID groupID, QVector<AnswerID> answers);
    QString candidateID() const;
    void setCandidateID(const QString &candidateID);
    GroupID groupID() const;
    void setGroupID(const GroupID &groupID);
    QVector<AnswerID> answers() const;
    void setAnswers(const QVector<AnswerID> &answers);
    double points() const;
    void setPoints(double points);
    bool valid() const;
    void setValid(bool valid);
};

#endif // FINISHEDEXAM_H
