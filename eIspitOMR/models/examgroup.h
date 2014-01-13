#ifndef EXAMGROUP_H
#define EXAMGROUP_H

#include <enumerations.h>
#include <qList>

class ExamGroup
{
    GroupID _id;
    QList<AnswerID> _answers;
public:
    ExamGroup();
    ExamGroup(GroupID id, QList<AnswerID> answers);

    int numberOfQuestions() const;
    GroupID id() const;
    void setId(const GroupID &id);
    QList<AnswerID> answers() const;
    void setAnswers(QList<AnswerID> answers);
};

#endif // EXAMGROUP_H
