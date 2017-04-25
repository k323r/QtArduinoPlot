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

    //ui->customPlot = new QCustomPlot(ui->centralWidget);
    //QCustomPlot *customPlot;
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->customPlot->graph(0)->setAntialiasedFill(false);
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));

    ui->customPlot->addGraph(); // blue dot
    ui->customPlot->graph(2)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->addGraph(); // red dot
    ui->customPlot->graph(3)->setPen(QPen(Qt::red));
    ui->customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(2);
    ui->customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
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
    char buffer[4];
    buffer[0] = block[0];
    buffer[1] = block[1];
    buffer[2] = block[2];
    buffer[3] = block[3];

    float in_value1 = *(float *)&buffer;

    buffer[0] = block[4];
    buffer[1] = block[5];
    buffer[2] = block[6];
    buffer[3] = block[7];

    float in_value2 = *(float *)&buffer;

    qInfo() << "values are here!";

    if (! ( fabs(in_value1) < SMALL) and !(fabs(in_value2) < SMALL)) {
        qInfo() << "value1: " << in_value1;
        qInfo() << "value2: " << in_value2;

        // calculate two new data points:
        #if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
            double key = 0;
        #else
            double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
        #endif

        static double lastPointKey = 0;

        if (key-lastPointKey > 0.002) {
            ui->customPlot->graph(0)->addData(key, in_value1);
            ui->customPlot->graph(0)->removeDataBefore(key-8);

            ui->customPlot->graph(1)->addData(key, in_value2);
            ui->customPlot->graph(1)->removeDataBefore(key-8);

            ui->customPlot->graph(0)->rescaleValueAxis();

            lastPointKey = key;
        }

        ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
        ui->customPlot->replot();

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key-lastFpsKey > 2) { // average fps over 2 seconds

            ui->statusBar->showMessage(
                QString("%1 FPS, Total Data points: %2")
                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
                    , 0);
            lastFpsKey = key;
            frameCount = 0;
        }
    }
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
    ui->connect->setDisabled(true);
    connected = true;
    ui->statusBar->showMessage( QString("connected"), 0);
}

void MainWindow::on_disconnect_clicked()
{
    if (connected) {
        serial->disconnect();
    }
    ui->connect->setDisabled(false);
    qInfo("disconnected");
    ui->statusBar->showMessage( QString("disconnected"), 0);
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

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
  Q_UNUSED(customPlot)
}
