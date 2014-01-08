#include "question.h"

Question::Question() {}

Question::Question(int id, int answer_id):
    _id(id), _answer_id(answer_id) {}

int Question::id() const
{
    return _id;
}

void Question::setId(int id)
{
    _id = id;
}

int Question::answer_id() const
{
    return _answer_id;
}

void Question::setAnswer_id(int answer_id)
{
    _answer_id = answer_id;
}

