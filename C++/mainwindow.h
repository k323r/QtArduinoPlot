#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtCore>
#include <QtDebug>
#include <QSerialPort>
#include "qcustomplot.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_deviceAdress_returnPressed();

    void readData();

    void on_connect_clicked();

    void on_disconnect_clicked();

    void on_baud1_clicked();

    void on_baud2_clicked();

    void on_baud3_clicked();

    void on_baud4_clicked();

    void setupPlayground(QCustomPlot *customPlot);

private:
    Ui::MainWindow *ui;
    QTimer dataTimer;
};

#endif // MAINWINDOW_H
