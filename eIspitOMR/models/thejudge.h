#ifndef THEJUDGE_H
#define THEJUDGE_H

#include <enumerations.h>
#include <exam.h>
#include <finishedexam.h>
#include <QList>
#include <imageprocessor.h>

class TheJudge
{
    static const double points_per_correct_answer = 2;

    static void applyCriteria(const QList<AnswerID> &criteria, FinishedExam &exam);
    static void applyCriteria(const QList<AnswerID> &criteria, QList<FinishedExam> &exams);
public:
    static FinishedExam markOne(const QList<AnswerID> &answers, const QString &imagePath);
    static QList<FinishedExam> markMultiple(const QList<AnswerID> &answers, const QList<QString> &imagePaths);

};

#endif // THEJUDGE_H
