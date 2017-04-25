/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabs;
    QWidget *setup;
    QLineEdit *deviceAdress;
    QPushButton *connect;
    QPushButton *disconnect;
    QRadioButton *baud3;
    QRadioButton *baud2;
    QRadioButton *baud1;
    QRadioButton *baud4;
    QWidget *measure;
    QWidget *livefeed;
    QCustomPlot *customPlot;
    QMenuBar *menuBar;
    QMenu *menuLivePlotter;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 599);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabs = new QTabWidget(centralWidget);
        tabs->setObjectName(QStringLiteral("tabs"));
        tabs->setGeometry(QRect(10, 0, 781, 531));
        setup = new QWidget();
        setup->setObjectName(QStringLiteral("setup"));
        deviceAdress = new QLineEdit(setup);
        deviceAdress->setObjectName(QStringLiteral("deviceAdress"));
        deviceAdress->setGeometry(QRect(140, 20, 151, 23));
        connect = new QPushButton(setup);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(300, 20, 83, 23));
        disconnect = new QPushButton(setup);
        disconnect->setObjectName(QStringLiteral("disconnect"));
        disconnect->setGeometry(QRect(400, 20, 83, 23));
        baud3 = new QRadioButton(setup);
        baud3->setObjectName(QStringLiteral("baud3"));
        baud3->setGeometry(QRect(10, 70, 109, 21));
        baud2 = new QRadioButton(setup);
        baud2->setObjectName(QStringLiteral("baud2"));
        baud2->setGeometry(QRect(10, 40, 109, 21));
        baud1 = new QRadioButton(setup);
        baud1->setObjectName(QStringLiteral("baud1"));
        baud1->setGeometry(QRect(10, 10, 109, 21));
        baud4 = new QRadioButton(setup);
        baud4->setObjectName(QStringLiteral("baud4"));
        baud4->setGeometry(QRect(10, 100, 109, 21));
        baud4->setChecked(true);
        tabs->addTab(setup, QString());
        measure = new QWidget();
        measure->setObjectName(QStringLiteral("measure"));
        tabs->addTab(measure, QString());
        livefeed = new QWidget();
        livefeed->setObjectName(QStringLiteral("livefeed"));
        customPlot = new QCustomPlot(livefeed);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(10, 10, 751, 471));
        tabs->addTab(livefeed, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 28));
        menuLivePlotter = new QMenu(menuBar);
        menuLivePlotter->setObjectName(QStringLiteral("menuLivePlotter"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuLivePlotter->menuAction());

        retranslateUi(MainWindow);

        tabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        deviceAdress->setText(QApplication::translate("MainWindow", "/dev/ttyUSB0", Q_NULLPTR));
        connect->setText(QApplication::translate("MainWindow", "connect", Q_NULLPTR));
        disconnect->setText(QApplication::translate("MainWindow", "disconnect", Q_NULLPTR));
        baud3->setText(QApplication::translate("MainWindow", "57600", Q_NULLPTR));
        baud2->setText(QApplication::translate("MainWindow", "38400", Q_NULLPTR));
        baud1->setText(QApplication::translate("MainWindow", "9600", Q_NULLPTR));
        baud4->setText(QApplication::translate("MainWindow", "115200", Q_NULLPTR));
        tabs->setTabText(tabs->indexOf(setup), QApplication::translate("MainWindow", "Setup", Q_NULLPTR));
        tabs->setTabText(tabs->indexOf(measure), QApplication::translate("MainWindow", "Measure", Q_NULLPTR));
        tabs->setTabText(tabs->indexOf(livefeed), QApplication::translate("MainWindow", "Livefeed", Q_NULLPTR));
        menuLivePlotter->setTitle(QApplication::translate("MainWindow", "livePlotter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
