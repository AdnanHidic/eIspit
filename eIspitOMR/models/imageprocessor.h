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
    // zuban metode
    static Mat prepare(Mat img);

    // hidex metode
    static FinishedExam extract(Mat img);
public:
    static FinishedExam load_exam(QString path);
};

#endif // IMAGEPROCESSOR_H
