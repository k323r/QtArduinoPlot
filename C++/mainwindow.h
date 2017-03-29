#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtDebug>
#include <QSerialPort>


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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
