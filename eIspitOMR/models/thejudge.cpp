#include "thejudge.h"

void TheJudge::applyCriteria(const QList<AnswerID> &criteria, FinishedExam &exam)
{
    double points;
    points = 0;
    for (int i=0; i < criteria.size();i++){
        if (exam.answers()[i]==criteria[i])
            points+=points_per_correct_answer;
    }
    exam.setPoints(points);
}

void TheJudge::applyCriteria(const QList<AnswerID> &criteria, QList<FinishedExam> &exams)
{
    foreach (FinishedExam exam, exams) {
        applyCriteria(criteria,exam);
    }
}

FinishedExam TheJudge::markOne(const QList<AnswerID> &answers, const QString &imagePath)
{
    FinishedExam exam;

    // first load the image, handle execeptions
    exam = ImageProcessor::load_exam(imagePath);

    // then mark the exam
    applyCriteria(answers,exam);

    // return the result
    return exam;
}

QList<FinishedExam> TheJudge::markMultiple(const QList<AnswerID> &answers, const QList<QString> &imagePaths)
{
    QList<FinishedExam> exams;

    foreach (QString imagePath, imagePaths){
        exams.append(markOne(answers,imagePath));
    }

    // return the result
    return exams;
}
