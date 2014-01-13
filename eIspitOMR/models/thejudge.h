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
    static void applyCriteria(const QList<AnswerID> &answers, FinishedExam &exam);
    static QList<AnswerID> findAnswersForGroup(const QList<ExamGroup> &groups, GroupID group_id);
    static FinishedExam markOne(const QList<ExamGroup> &groups, const QString &imagePath);
public:
    static QList<FinishedExam> *mark(const QList<ExamGroup> &groups, const QList<QString> &imagePaths);

};

#endif // THEJUDGE_H
