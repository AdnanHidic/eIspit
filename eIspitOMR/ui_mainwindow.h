/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_exam;
    QAction *actionQuit;
    QAction *actionSave_results;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *loadImagesTab;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addImagesButton;
    QPushButton *removeImagesButton;
    QListWidget *imageListWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *markButton;
    QPushButton *saveResultsButton;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(542, 373);
        MainWindow->setAnimated(false);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        actionLoad_exam = new QAction(MainWindow);
        actionLoad_exam->setObjectName(QStringLiteral("actionLoad_exam"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionSave_results = new QAction(MainWindow);
        actionSave_results->setObjectName(QStringLiteral("actionSave_results"));
        actionSave_results->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        loadImagesTab = new QWidget();
        loadImagesTab->setObjectName(QStringLiteral("loadImagesTab"));
        verticalLayout_3 = new QVBoxLayout(loadImagesTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_2 = new QWidget(loadImagesTab);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        addImagesButton = new QPushButton(widget_3);
        addImagesButton->setObjectName(QStringLiteral("addImagesButton"));

        horizontalLayout_3->addWidget(addImagesButton);

        removeImagesButton = new QPushButton(widget_3);
        removeImagesButton->setObjectName(QStringLiteral("removeImagesButton"));

        horizontalLayout_3->addWidget(removeImagesButton);


        horizontalLayout_4->addWidget(widget_3, 0, Qt::AlignLeft|Qt::AlignVCenter);


        verticalLayout->addWidget(widget_2, 0, Qt::AlignTop);

        imageListWidget = new QListWidget(loadImagesTab);
        imageListWidget->setObjectName(QStringLiteral("imageListWidget"));
        imageListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        imageListWidget->setAlternatingRowColors(true);
        imageListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        imageListWidget->setSelectionRectVisible(true);
        imageListWidget->setSortingEnabled(false);

        verticalLayout->addWidget(imageListWidget);


        verticalLayout_3->addLayout(verticalLayout);

        tabWidget->addTab(loadImagesTab, QString());

        verticalLayout_2->addWidget(tabWidget);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        horizontalLayout_2->addLayout(horizontalLayout);

        markButton = new QPushButton(widget);
        markButton->setObjectName(QStringLiteral("markButton"));

        horizontalLayout_2->addWidget(markButton);

        saveResultsButton = new QPushButton(widget);
        saveResultsButton->setObjectName(QStringLiteral("saveResultsButton"));
        saveResultsButton->setEnabled(false);

        horizontalLayout_2->addWidget(saveResultsButton);


        verticalLayout_2->addWidget(widget, 0, Qt::AlignRight|Qt::AlignVCenter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 542, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_exam);
        menuFile->addAction(actionSave_results);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionLoad_exam, SIGNAL(triggered()), MainWindow, SLOT(loadExamFile()));
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(quit()));
        QObject::connect(addImagesButton, SIGNAL(clicked()), MainWindow, SLOT(loadExamImages()));
        QObject::connect(removeImagesButton, SIGNAL(clicked()), MainWindow, SLOT(removeExamImages()));
        QObject::connect(markButton, SIGNAL(clicked()), MainWindow, SLOT(mark()));
        QObject::connect(imageListWidget, SIGNAL(itemSelectionChanged()), MainWindow, SLOT(imageListItemSelectionChanged()));
        QObject::connect(actionSave_results, SIGNAL(triggered()), MainWindow, SLOT(saveExamResults()));
        QObject::connect(saveResultsButton, SIGNAL(clicked()), MainWindow, SLOT(saveExamResults()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "The Judge v0.0.1", 0));
        actionLoad_exam->setText(QApplication::translate("MainWindow", "Load exam", 0));
        actionLoad_exam->setShortcut(QApplication::translate("MainWindow", "F2", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "F12", 0));
        actionSave_results->setText(QApplication::translate("MainWindow", "Save results", 0));
        addImagesButton->setText(QApplication::translate("MainWindow", "Add image(s)", 0));
        removeImagesButton->setText(QApplication::translate("MainWindow", "Remove selected image(s)", 0));
        tabWidget->setTabText(tabWidget->indexOf(loadImagesTab), QApplication::translate("MainWindow", "Load images", 0));
        markButton->setText(QApplication::translate("MainWindow", "Mark", 0));
        saveResultsButton->setText(QApplication::translate("MainWindow", "Save results", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
