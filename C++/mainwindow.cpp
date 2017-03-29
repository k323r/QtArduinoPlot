#include "mainwindow.h"
#include "ui_mainwindow.h"

QSerialPort *serial;
QString device = "/dev/ttyUSB0";
qint32 baudRate = 115200;
bool connected = false;

char serialBuffer[24];
//char in = 0.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qInfo("hello, world");
    ui->connect->setDisabled(false);
}

MainWindow::~MainWindow()
{
    if (connected) {
        serial->close();
    }
    delete ui;
}


void MainWindow::on_deviceAdress_returnPressed()
{

}

void MainWindow::readData() {
//    QByteArray single = serial->read(1);
    QByteArray block;
    block = serial->readLine();
    qInfo() << block;
//    if (single.toStdString() == "S") {
//        block = serial->read(24);
//    }
    

}

void MainWindow::on_connect_clicked()
{
    serial = new QSerialPort(this);
    device = ui->deviceAdress->text();
    qInfo() << "Device address: " << device;
    serial->setPortName(device);
    serial->open(QIODevice::ReadOnly);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    qInfo("connected");
//    qInfo() << "first byte: " << serial->read(1);
    connected = true;
}

void MainWindow::on_disconnect_clicked()
{
    if (connected) {
        serial->disconnect();
    }
    qInfo("disconnected");
}

void MainWindow::on_baud1_clicked()
{
    if (!connected) {
        baudRate = 9600;
    }
    qInfo("baud 9600 activated");
}

void MainWindow::on_baud2_clicked()
{
    if (!connected) {
        baudRate = 38400;
    }
    qInfo("baud 38400 activated");
}

void MainWindow::on_baud3_clicked()
{
    if (!connected) {
        baudRate = 57600;
    }
    qInfo("baud 57600 activated");
}

void MainWindow::on_baud4_clicked()
{
    if (!connected) {
        baudRate = 115200;
    }
    qInfo("baud 115200 activated");
}

