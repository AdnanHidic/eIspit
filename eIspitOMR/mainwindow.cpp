#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enumerations.h"
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theJudge = new TheJudge();
    loadedExam = 0;
    finishedExams = 0;

    this->ui->tabWidget->setEnabled(false);
    this->ui->addImagesButton->setEnabled(false);
    this->ui->removeImagesButton->setEnabled(false);
    this->ui->markButton->setEnabled(false);
    this->ui->actionSave_results->setEnabled(false);
    this->ui->saveResultsButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete theJudge;
    delete loadedExam;
    delete finishedExams;
}

void MainWindow::mark()
{
    if (finishedExams != 0)
    {
        delete finishedExams;
    }

    // @Zuba/Hidex
    // Ovdje pozovite svoju metodu koja vraca pointer na finalnu QList<FinishedExams>
    // Imate dostupnu QListu grupa sa loadedExam->examGroups(), i QListu putanja do slika sa loadedImages()
    // rezultat dodijelite finishedExams varijabli.
    //
    // npr:
    finishedExams = theJudge->mark(loadedExam->examgroups(), loadedImages());

    if (finishedExams && finishedExams->count() > 0)
    {
        QMessageBox::information(this, "Mark", "Exams have been successfully marked", QMessageBox::Ok);
        this->ui->actionSave_results->setEnabled(true);
        this->ui->saveResultsButton->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, "Mark", "None of the exams have been marked", QMessageBox::Ok);
        this->ui->actionSave_results->setEnabled(false);
        this->ui->saveResultsButton->setEnabled(false);
    }
}

void MainWindow::loadExamFile()
{
    QFileDialog openFileDialog(this);
    openFileDialog.setFileMode(QFileDialog::ExistingFile);
    openFileDialog.setNameFilter(tr("eIspit exam file (*.exam)"));
    openFileDialog.setDefaultSuffix(tr("exam"));

    QStringList selectedFilenames;
    if (openFileDialog.exec())
    {
        selectedFilenames = openFileDialog.selectedFiles();

        if (selectedFilenames.count() > 0)
        {
            QFile examFile(selectedFilenames.first());
            if (examFile.open(QFile::ReadOnly))
            {
                QJsonDocument examJson = QJsonDocument::fromJson(examFile.readAll());
                examFile.close();

                if (examJson.isNull() || !examJson.isObject())
                {
                    QMessageBox::critical(this, "Load exam", "Specified file does not contain valid JSON", QMessageBox::Ok);
                    return;
                }

                Exam *tmpExam = new Exam();

                if (examJson.object().value(ExamHeaders::Name).isString())
                {
                    tmpExam->setName(examJson.object().value(ExamHeaders::Name).toString());
                }
                else
                {
                    QMessageBox::critical(this, "Load exam", "Exam name is missing", QMessageBox::Ok);
                    delete tmpExam;
                    return;
                }

                QList<ExamGroup> tmpExamGroupList;

                if (examJson.object().value(ExamHeaders::Groups).isArray())
                {
                    foreach (QJsonValue examGroupJson, examJson.object().value(ExamHeaders::Groups).toArray())
                    {
                        if (examGroupJson.isObject() && examGroupJson.toObject().value(ExamHeaders::GroupName).isString())
                        {
                            QString examGroupName = examGroupJson.toObject().value(ExamHeaders::GroupName).toString();
                            GroupID groupId;

                            if (examGroupName == GroupName::A)
                            {
                                groupId = GroupID_A;
                            }
                            else if (examGroupName == GroupName::B)
                            {
                                groupId = GroupID_B;
                            }
                            else if (examGroupName == GroupName::C)
                            {
                                groupId = GroupID_C;
                            }
                            else if (examGroupName == GroupName::D)
                            {
                                groupId = GroupID_D;
                            }
                            else if (examGroupName == GroupName::E)
                            {
                                groupId = GroupID_E;
                            }
                            else if (examGroupName == GroupName::F)
                            {
                                groupId = GroupID_F;
                            }
                            else if (examGroupName == GroupName::G)
                            {
                                groupId = GroupID_G;
                            }
                            else if (examGroupName == GroupName::H)
                            {
                                groupId = GroupID_H;
                            }
                            else
                            {
                                QMessageBox::critical(this, "Load exam", "Invalid or missing group name", QMessageBox::Ok);
                                delete tmpExam;
                                return;
                            }

                            QList<AnswerID> tmpAnswers;

                            if (examGroupJson.toObject().value(ExamHeaders::Answers).isArray())
                            {
                                foreach (QJsonValue groupAnswerJson, examGroupJson.toObject().value(ExamHeaders::Answers).toArray())
                                {
                                    if (groupAnswerJson.isString())
                                    {
                                        QString examGroupAnswer = groupAnswerJson.toString();
                                        AnswerID answerId;

                                        if (examGroupAnswer == AnswerName::A)
                                        {
                                            answerId = AnswerID_A;
                                        }
                                        else if (examGroupAnswer == AnswerName::B)
                                        {
                                            answerId = AnswerID_B;
                                        }
                                        else if (examGroupAnswer == AnswerName::C)
                                        {
                                            answerId = AnswerID_C;
                                        }
                                        else if (examGroupAnswer == AnswerName::D)
                                        {
                                            answerId = AnswerID_D;
                                        }
                                        else
                                        {
                                            QMessageBox::critical(this, "Load exam", "Invalid or missing group answer", QMessageBox::Ok);
                                            delete tmpExam;
                                            return;
                                        }

                                        tmpAnswers.append(answerId);
                                    }
                                    else
                                    {
                                        QMessageBox::critical(this, "Load exam", "Invalid or missing group answer", QMessageBox::Ok);
                                        delete tmpExam;
                                        return;
                                    }
                                }
                            }
                            else
                            {
                                QMessageBox::critical(this, "Load exam", "Invalid or missing group answers", QMessageBox::Ok);
                                delete tmpExam;
                                return;
                            }

                            tmpExamGroupList.append(ExamGroup(groupId, tmpAnswers));
                        }
                        else
                        {
                            QMessageBox::critical(this, "Load exam", "Invalid or missing group name", QMessageBox::Ok);
                            delete tmpExam;
                            return;
                        }
                    }
                    tmpExam->setExamgroups(tmpExamGroupList);
                }
                else
                {
                    QMessageBox::critical(this, "Load exam", "Invalid or missing groups", QMessageBox::Ok);
                    delete tmpExam;
                    return;
                }

                loadedExam = tmpExam;
            }
            else
            {
                QMessageBox::critical(this, "Load exam", "Could not open specified file", QMessageBox::Ok);
            }
        }

        loadedExamFile();
    }
}

void MainWindow::loadedExamFile()
{
    this->setWindowTitle(QString("The Judge v0.0.1 - " + loadedExam->name()));

    QMessageBox::information(this, "Load exam", loadedExam->name() + " has been successfully loaded.\nGroups: " + QString::number(loadedExam->examgroups().count()) + "\nAnswers per group: " + QString::number(loadedExam->examgroups()[0].answers().count()), QMessageBox::Ok);

    this->ui->imageListWidget->clear();
    this->ui->tabWidget->setEnabled(true);
    this->ui->addImagesButton->setEnabled(true);
    this->ui->removeImagesButton->setEnabled(false);
    this->ui->markButton->setEnabled(false);
    this->ui->actionSave_results->setEnabled(false);
    this->ui->saveResultsButton->setEnabled(false);
}

void MainWindow::loadExamImages()
{
    QFileDialog openFileDialog(this);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);
    openFileDialog.setNameFilter(tr("Images (*.jpg *.png *.bmp)"));

    QStringList selectedFilenames;
    if (openFileDialog.exec())
    {
        selectedFilenames = openFileDialog.selectedFiles();

        if (selectedFilenames.count() > 0)
        {
            foreach(QString filename, selectedFilenames)
            {

                if (filename.endsWith(".png") || filename.endsWith(".bmp") || filename.endsWith(".jpg") || filename.endsWith(".png"))
                {
                    QList<QListWidgetItem *> exactItems = this->ui->imageListWidget->findItems(filename, Qt::MatchFixedString);

                    if (exactItems.count() == 0)
                    {
                        this->ui->imageListWidget->addItem(new QListWidgetItem(filename));
                    }
                }
            }

            this->ui->markButton->setEnabled(true);
        }
    }
}

void MainWindow::removeExamImages()
{
    if (this->ui->imageListWidget->selectedItems().count() > 0)
    {
        foreach(QListWidgetItem *imagePath, this->ui->imageListWidget->selectedItems())
        {
            this->ui->imageListWidget->takeItem(this->ui->imageListWidget->row(imagePath));
            delete imagePath;
        }
    }
}

void MainWindow::imageListItemSelectionChanged()
{
    if (this->ui->imageListWidget->count() == 0)
    {
        this->ui->markButton->setEnabled(false);
    }

    if (this->ui->imageListWidget->selectedItems().count() > 0)
    {
        this->ui->removeImagesButton->setEnabled(true);
    }
    else
    {
        this->ui->removeImagesButton->setEnabled(false);
    }
}

QStringList MainWindow::loadedImages()
{
    QList<QListWidgetItem *> imageListWidgetItems = this->ui->imageListWidget->findItems("", Qt::MatchContains);

    QStringList imagePathList;

    foreach(QListWidgetItem *imageListWidgetItem, imageListWidgetItems)
    {
        imagePathList.append(imageListWidgetItem->text());
    }

    return imagePathList;
}

void MainWindow::saveExamResults()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save results", "results.csv", "CSV files (*.csv)", 0, 0);

    if (!filename.isEmpty())
    {
        QFile data(filename);
        if (data.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream output(&data);
            output << "\"Candidate ID\",\"Group\",\"Total points\"";
            output << endl;

            foreach(FinishedExam e, *finishedExams)
            {
                output << "\"" << e.candidateID() << "\",";

                QString groupName;

                if (e.groupID() == GroupID_A)
                {
                    groupName = GroupName::A;
                }
                else if (e.groupID() == GroupID_B)
                {
                    groupName = GroupName::B;
                }
                else if (e.groupID() == GroupID_C)
                {
                    groupName = GroupName::C;
                }
                else if (e.groupID() == GroupID_D)
                {
                    groupName = GroupName::D;
                }
                else if (e.groupID() == GroupID_E)
                {
                    groupName = GroupName::E;
                }
                else if (e.groupID() == GroupID_F)
                {
                    groupName = GroupName::F;
                }
                else if (e.groupID() == GroupID_G)
                {
                    groupName = GroupName::G;
                }
                else
                {
                    groupName = "Unknown";
                }

                output << "\"" << groupName << "\",";
                output << "\"" << e.points() << "\"";
                output << endl;
            }

            QMessageBox::information(this, "Save results", "Results have been successfuly exported", QMessageBox::Ok);

        }
    }
}

void MainWindow::quit()
{
    QApplication::quit();
}
