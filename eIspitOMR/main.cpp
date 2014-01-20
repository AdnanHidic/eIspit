#include "mainwindow.h"
#include <QMessageBox>
#include "imagepreprocessor.h"
#include <QApplication>
#include <QTime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    /*QTime myTimer;
    myTimer.start();
    Mat novo = ImagePreprocessor::prepare(image);
    int nMilliseconds = myTimer.elapsed();
    imshow("Tess",novo);*/



    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();

    return 0;
}
