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

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
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

    float in_value = *(float *)&buffer;

    qInfo() << "value: " << in_value;

//    qInfo() << "length : " << block.length();

    // calculate two new data points:
    #if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
        double key = 0;
    #else
        double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    #endif

    static double lastPointKey = 0;

    if (key-lastPointKey > 0.001) {

      //double value0 = sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
      //double value0 = serial->read()
      //double value1 = sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;

      //double value0 = tan(key);  //qSin(key); //sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
      //double value1 = -tan(key); //qCos(key); //sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;


      // add data to lines:
      ui->customPlot->graph(0)->addData(key, in_value);
      //ui->customPlot->graph(1)->addData(key, value1);
      // set data of dots:
      //ui->customPlot->graph(2)->clearData();
      //ui->customPlot->graph(2)->addData(key, value0);
      //ui->customPlot->graph(3)->clearData();
      //ui->customPlot->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      ui->customPlot->graph(0)->removeDataBefore(key-8);
      //ui->customPlot->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->customPlot->replot();



//    qInfo() << block[0] << block[1] << block[2] << block[3];


//    quint32 tmp1 = ((char)block[3] << 24) | ((char)block[2] << 16) | ((char)block[1] << 8) | (char)block[0];
//    qInfo() <<  *( reinterpret_cast<float*> (&tmp1) );

//    quint32 tmp2 = ((char)block[4] << 24) | ((char)block[5] << 16) | ((char)block[6] << 8) | (char)block[7];
//    qInfo() <<  *( reinterpret_cast<float*> (&tmp2) );


/*
    if (nBytes % 4 == 0) {
        qInfo() << "working";
        for(int i = 0; i < nBytes; i = i + 4) {
            qInfo() << "i : " << i;
            quint32 tmp = ((char)block[i + 3] << 24) | ((char)block[i + 2] << 16) | ((char)block[i + 1] << 8) | (char)block[i];
            // float *tOut = reinterpret_cast<float*>(&tmp);
            // values[i/4] = *tOut;
            // values[i/4] = *( reinterpret_cast<float*> (&tmp) );
            qInfo() << "index: " << i/4 << " : " << *( reinterpret_cast<float*> (&tmp) );
        }
    }

//    qInfo() << values[0];
//    qInfo() << values[1];
//    float *out = reinterpret_cast<float*>(&tmp);
//    qInfo() << "float" << *out;
//    if (single.toStdString() == "S") {
//        block = serial->read(24);
//    }
*/

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
}

void MainWindow::on_disconnect_clicked()
{
    if (connected) {
        serial->disconnect();
    }
    ui->connect->setDisabled(false);
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

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
  Q_UNUSED(customPlot)
}
