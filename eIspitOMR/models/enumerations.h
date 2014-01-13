#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

#include <QString>

enum AnswerID {
    AnswerID_NONE = 0,
    AnswerID_A,
    AnswerID_B,
    AnswerID_C,
    AnswerID_D
};

enum GroupID {
    GroupID_NONE = 0,
    GroupID_A,
    GroupID_B,
    GroupID_C,
    GroupID_D,
    GroupID_E,
    GroupID_F,
    GroupID_G,
    GroupID_H
};

struct AnswerName {
    static const QString NONE;
    static const QString A;
    static const QString B;
    static const QString C;
    static const QString D;
};

struct GroupName {
    static const QString A;
    static const QString B;
    static const QString C;
    static const QString D;
    static const QString E;
    static const QString F;
    static const QString G;
    static const QString H;
};


struct ExamHeaders {
    static const QString Name;
    static const QString Groups;
    static const QString GroupName;
    static const QString Answers;
};

#endif // ENUMERATIONS_H
