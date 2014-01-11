#include "imageprocessor.h"

QList<FinishedExam> ImageProcessor::load_exams(QList<QString> paths)
{
    QList<FinishedExam> exams;

    FinishedExam loaded_from_image;
    foreach (QString path, paths){
        loaded_from_image = load_exam(path);
        exams.append(loaded_from_image);
    }

    return exams;
}

FinishedExam ImageProcessor::load_exam(QString path)
{
    FinishedExam exam;
    // place where magic happens
    Mat img = imread(path.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);

    // if the image could not be loaded, handle the unpleasantries
    if (img.data==NULL){
        // how?
    }

    return exam;
}
