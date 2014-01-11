#include "examgroup.h"

ExamGroup::ExamGroup()
{
}

ExamGroup::ExamGroup(GroupID id, QList<AnswerID> answers):
    _id(id), _answers(answers)
{

}

GroupID ExamGroup::id() const
{
    return _id;
}

void ExamGroup::setId(const GroupID &id)
{
    _id = id;
}

QList<AnswerID> ExamGroup::answers() const
{
    return _answers;
}

void ExamGroup::setAnswers(const QList<AnswerID> &answers)
{
    _answers = answers;
}

int ExamGroup::numberOfQuestions() const
{
    return _answers.size();
}
