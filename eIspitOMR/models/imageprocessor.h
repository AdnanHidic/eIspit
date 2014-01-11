#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QList>
#include <QString>
#include <finishedexam.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class ImageProcessor
{
public:
    static QList<FinishedExam> load_exams(QList<QString> paths);
    static FinishedExam load_exam(QString path);
};

#endif // IMAGEPROCESSOR_H
