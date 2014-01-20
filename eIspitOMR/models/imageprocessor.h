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
    static QVector<AnswerID> extract_answers(const Mat &img);

    static QVector<int> count_pixels_by_column(const Mat &img, int startX, int startY, int diffY, int num);
    static QVector<int> count_pixels_by_row(Mat &img, int startX, int startY, int diffX, int num);

    static const double group_success_pct = 0.3;
    static const double answ_success_pct = 0.3;

    static const int bbox_height = 10;
    static const int bbox_width = 10;
    static const int group_bbox_x_coordinates[];
    static const int group_bbox_y_coordinate = 9;

    static const int cid_bbox_x_start = 13;
    static const int cid_bbox_y_start = 7;
    static const int cid_bbox_x_offset = 24;
    static const int cid_bbox_y_offset = 21;

    static const int answ_ROI_x_start = 386;
    static const int answ_ROI_y_start = 244;
    static const int answ_ROI_x_offset = 100;
    static const int answ_ROI_y_offset = 502;

    static const int answ_bbox_x_start = 3;
    static const int answ_bbox_y_start = 4;
    static const int answ_bbox_x_offset = 25;
    static const int answ_bbox_y_offset = 25;

    static const QString groupchars[];
    static const QString groupnums[];
public:
    static FinishedExam load_exam(QString path);
};

#endif // IMAGEPROCESSOR_H
