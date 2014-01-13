#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QStringList>
#include "exam.h"
#include "thejudge.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList loadedImages();

public slots:
    void loadExamFile();
    void loadExamImages();
    void removeExamImages();
    void imageListItemSelectionChanged();
    void saveExamResults();
    void mark();
    void quit();

private:
    Ui::MainWindow *ui;
    TheJudge *theJudge;
    Exam *loadedExam;
    QList<FinishedExam> *finishedExams;

    void loadedExamFile();
};

#endif // MAINWINDOW_H
