#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QList>
#include <QVector>
#include <QString>
#include <finishedexam.h>
#include <imagepreprocessor.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class ImageProcessor
{
    static FinishedExam extract(Mat img);
    static GroupID extract_group(const Mat &img);
    static QVector<int> count_pixels_group(const Mat &img);

    static const double group_success_pct = 0.7;
    static const int group_bbox_height = 10;
    static const int group_bbox_width = 10;
    static const int group_bbox_x_coordinates[];
    static const int group_bbox_y_coordinate = 7;
public:
    static FinishedExam load_exam(QString path);
};

#endif // IMAGEPROCESSOR_H
