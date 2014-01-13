#include "thejudge.h"

void TheJudge::applyCriteria(const QList<AnswerID> &answers, FinishedExam &exam)
{
    double points;
    points = 0;
    for (int i=0; i < answers.size();i++){
        if (exam.answers()[i]==answers[i])
            points+=points_per_correct_answer;
    }
    exam.setPoints(points);
}

QList<AnswerID> TheJudge::findAnswersForGroup(const QList<ExamGroup> &groups, GroupID group_id)
{
    QList<AnswerID> answers;
    for (int i=0;i<groups.size();i++){
        if (groups[i].id()==group_id){
            answers = groups[i].answers();
            break;
        }
    }
    return answers;
}

FinishedExam TheJudge::markOne(const QList<ExamGroup> &groups, const QString &imagePath)
{
    FinishedExam exam;

    // first we get the exam from imagepath
    exam = ImageProcessor::load_exam(imagePath);

    // then we find the correct group
    QList<AnswerID> answers = findAnswersForGroup(groups,exam.groupID());

    // then mark the exam
    applyCriteria(answers,exam);

    // return the result
    return exam;
}

QList<FinishedExam> TheJudge::mark(const QList<ExamGroup> &groups, const QList<QString> &imagePaths)
{
    QList<FinishedExam> exams;

    foreach (QString imagePath, imagePaths){
        exams.append(markOne(groups,imagePath));
    }

    // return the result
    return exams;
}
