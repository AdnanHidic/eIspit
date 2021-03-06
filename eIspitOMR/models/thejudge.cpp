#include "thejudge.h"

void TheJudge::applyCriteria(const QVector<AnswerID> &answers, FinishedExam &exam)
{
    double points;
    points = 0;
    for (int i=0; i < answers.size();i++){
        if (exam.answers()[i]==answers[i])
            points+=points_per_correct_answer;
    }
    exam.setPoints(points);
}

QVector<AnswerID> TheJudge::findAnswersForGroup(const QList<ExamGroup> &groups, GroupID group_id)
{
    QVector<AnswerID> answers;
    for (int i=0;i<groups.size();i++){
        if (groups[i].id()==group_id){
            answers = groups[i].answers().toVector();
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

    // if something went wrong
    if (!exam.valid())
        return exam;

    // else if everything is okay, we find the correct group
    QVector<AnswerID> answers = findAnswersForGroup(groups,exam.groupID());

    // if there is no such group
    if (answers.size()==0){
        exam.setValid(false);
        return exam;
    }

    // else, we mark the exam
    applyCriteria(answers,exam);

    // return the result
    return exam;
}

QList<FinishedExam>* TheJudge::mark(const QList<ExamGroup> &groups, const QList<QString> &imagePaths)
{
    QList<FinishedExam> *exams = new QList<FinishedExam>();

    foreach (QString imagePath, imagePaths){
        exams->append(markOne(groups,imagePath));
    }

    // return the result
    return exams;
}
