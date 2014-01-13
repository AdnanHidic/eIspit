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

    static QString extract_candidateID(const Mat &img);
    static QVector<int> count_pixels_by_column(const Mat &img, int startX, int startY, int diffY, int num);

    static QList<AnswerID> extract_answers(const Mat &img);

    static const double group_success_pct = 0.7;
    static const int bbox_height = 10;
    static const int bbox_width = 10;
    static const int group_bbox_x_coordinates[];
    static const int group_bbox_y_coordinate = 7;

    static const int cid_bbox_x_start = 13;
    static const int cid_bbox_y_start = 7;
    static const int cid_bbox_x_offset = 24;
    static const int cid_bbox_y_offset = 21;

    static const QString groupchars[];
    static const QString groupnums[];
public:
    static FinishedExam load_exam(QString path);
};

#endif // IMAGEPROCESSOR_H
