#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_deviceAdress_returnPressed()
{

}

void MainWindow::on_connect_clicked()
{

}

void MainWindow::on_disconnect_clicked()
{

}

void MainWindow::on_baud1_clicked()
{

}

void MainWindow::on_baud2_clicked()
{

}

void MainWindow::on_baud3_clicked()
{

}

void MainWindow::on_baud4_clicked()
{

}

