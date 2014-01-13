#ifndef IMAGEPREPROCESSOR_H
#define IMAGEPREPROCESSOR_H

#include <QList>
#include <QVector>
#include <QString>
#include <finishedexam.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class ImagePreprocessor
{
public:
    static Mat prepare(Mat img);
};

#endif // IMAGEPREPROCESSOR_H
