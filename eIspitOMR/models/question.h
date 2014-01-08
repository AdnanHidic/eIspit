#ifndef QUESTION_H
#define QUESTION_H

class Question
{
    int _id;
    int _answer_id;
public:
    Question();
    Question(int id, int answer_id);
    int id() const;
    void setId(int id);
    int answer_id() const;
    void setAnswer_id(int answer_id);
};

#endif // QUESTION_H
