#include "mainwindow.h"
#include "imagepreprocessor.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat image = cv::imread("ispit_neobradjeno.jpg");
    imshow("Tess",ImagePreprocessor::prepare(image));

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();

    return 0;
}
