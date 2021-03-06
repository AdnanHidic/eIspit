#include "finishedexam.h"



bool FinishedExam::valid() const
{
    return _valid;
}

void FinishedExam::setValid(bool valid)
{
    _valid = valid;
}
FinishedExam::FinishedExam()
{
}

FinishedExam::FinishedExam(QString candidateID, GroupID groupID, QVector<AnswerID> answers):
    _candidateID(candidateID), _groupID(groupID), _answers(answers)
{

}

QString FinishedExam::candidateID() const
{
    return _candidateID;
}

void FinishedExam::setCandidateID(const QString &candidateID)
{
    _candidateID = candidateID;
}

GroupID FinishedExam::groupID() const
{
    return _groupID;
}

void FinishedExam::setGroupID(const GroupID &groupID)
{
    _groupID = groupID;
}

QVector<AnswerID> FinishedExam::answers() const
{
    return _answers;
}

void FinishedExam::setAnswers(const QVector<AnswerID> &answers)
{
    _answers = answers;
}

double FinishedExam::points() const
{
    return _points;
}

void FinishedExam::setPoints(double points)
{
    _points = points;
}
